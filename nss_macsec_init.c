/*
 * Copyright (c) 2014, 2018-2019 The Linux Foundation. All rights reserved.
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
 * SPDX-License-Identifier: ISC
 */


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netdevice.h>
#include <linux/phy.h>
#include <net/sock.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include "nss_macsec_sdk_api.h"
#include "nss_macsec_fal_api.h"
#include "nss_macsec.h"
#include "nss_macsec_utility.h"

/* DebugFS root directory */
static struct dentry *macsec_debugfs_root;

/* State string mapping - only used in this file */
static const char *macsec_state_strings[MACSEC_STATE_MAX] = {
	"Initial",
	"Success",
	"Netlink Init Failed",
	"Notifier Registration Failed",
	"Memory Allocation Failed",
	"SecY Initialization Failed",
	"Unregister Failed",
	"Removed"
};

/* Module statistics - only used in this file */
static struct macsec_module_stats macsec_stats = {
	.current_state = MACSEC_INIT,
	.register_count = ATOMIC_INIT(0),
	.unregister_count = ATOMIC_INIT(0),
};

/* Device debug info - shared across files, defined here */
struct macsec_device_debug macsec_device_debug[MACSEC_DEVICE_MAXNUM];

static struct sock *sdk_nl_sk = NULL;

static unsigned int nss_macsec_msg_handle(void *msg_data, unsigned int *sync)
{
	struct sdk_msg_header *header = (struct sdk_msg_header *)msg_data;
	unsigned short cmd_type = header->cmd_type;
	unsigned int ret = 0;

	*sync = 1;
	switch (cmd_type) {
	case SDK_FAL_CMD:{
			ret = nss_macsec_fal_msg_handle(header);
		}
		break;

	default:
		break;
	}

	return ret;
}

static void nss_macsec_netlink_recv(struct sk_buff *__skb)
{
	struct sk_buff *skb = NULL;
	struct nlmsghdr *nlh = NULL;
	struct sdk_msg_header *header = NULL;
	void *msg_data;
	u32 pid = 0, msg_type = 0, sync = 0, ret = 0, msg_len = 0;

	if ((skb = skb_clone(__skb, GFP_KERNEL)) != NULL) {
		nlh = nlmsg_hdr(skb);
		pid = nlh->nlmsg_pid;
		msg_data = NLMSG_DATA(nlh);
		msg_type = nlh->nlmsg_type;
		msg_len = sizeof(struct nlmsghdr) + sizeof(struct sdk_msg_header);
		header = (struct sdk_msg_header *)msg_data;
		if (header->buf_len > (U32_MAX - msg_len))
			return;
		msg_len += header->buf_len;

		if(skb->len < msg_len) {
			osal_print("Unexpected msg received! skb_len [0x%x] less than 0x%x\n",
				skb->len, msg_len);
			return;
		} else if (msg_type == SDK_CALL_MSG) {
			ret = nss_macsec_msg_handle(msg_data, &sync);
			header->ret = ret;
		} else {
			osal_print("Unexpected msg:0x%x received!\n", msg_type);
			return;
		}

		NETLINK_CB(skb).portid = 0; /* from kernel */
		NETLINK_CB(skb).dst_group = 0;	/* unicast */
		netlink_unicast(sdk_nl_sk, skb, pid, MSG_DONTWAIT);
	}

	return;
}

static int nss_macsec_netlink_init(void)
{
	struct netlink_kernel_cfg cfg = {
			.input	= nss_macsec_netlink_recv,
	};

	sdk_nl_sk = netlink_kernel_create(&init_net, NETLINK_SDK, &cfg);
	if (sdk_nl_sk == NULL) {
		osal_print("Create netlink socket fail\n");
		return -ENODEV;
	}

	return 0;
}

u32 nss_macsec_dt_secy_id_get(u8 *dev_name, u32 *secy_id)
{
	u32 dev_id = INVALID_DEVICE_ID;
	struct net_device *netdev = NULL;

	/* get net device by ifname */
	netdev = __dev_get_by_name(&init_net, (const char *)dev_name);
	if (unlikely(!netdev)) {
		*secy_id = INVALID_DEVICE_ID;
		/* no net device, return not found */
		return ERROR_NOT_FOUND;
	}

	/* get phydev by net device and find secy_id */
	if (netdev->phydev)
		dev_id = macsec_get_device_id(netdev->phydev);

	*secy_id = dev_id;

	return ERROR_OK;
}

static void nss_macsec_netlink_fini(void)
{
	if (sdk_nl_sk) {
		sock_release(sdk_nl_sk->sk_socket);
		sdk_nl_sk = NULL;
	}
}

static int nss_macsec_module_status_show(struct seq_file *m, void *v)
{
	u32 device_count = 0;
	int i;
	u32 dev_state;
	const char *state_str;

	/* Part 1: Global module state with aligned format */
	if (macsec_stats.current_state < MACSEC_STATE_MAX) {
		seq_printf(m, "%-27s : %s\n", "NSS_MACsec_Module_State",
			  macsec_state_strings[macsec_stats.current_state]);
	} else {
		seq_printf(m, "%-27s : unknown state %u\n",
				"NSS_MACsec_Module_State",
				macsec_stats.current_state);
	}

	seq_printf(m, "%-27s : %u\n", "register_count",
		   atomic_read(&macsec_stats.register_count));
	seq_printf(m, "%-27s : %u\n", "unregister_count",
		   atomic_read(&macsec_stats.unregister_count));

	/* Get active device count */
	device_count = qca_macsec_get_device_count();
	seq_printf(m, "%-27s : %u\n", "MACsec_device_count", device_count);

	/* Part 2: Device status - show all devices with debug state */
	for (i = 0; i < MACSEC_DEVICE_MAXNUM; i++) {
		if (macsec_device_debug[i].device_state != MACSEC_INIT) {
			dev_state = macsec_device_debug[i].device_state;
			state_str = (dev_state < MACSEC_STATE_MAX) ?
				    macsec_state_strings[dev_state] : "unknown";

			seq_printf(m, "Device %d\n", i);
			seq_printf(m, "    %-23s : %s\n", "Interface",
				   macsec_device_debug[i].interface_name);
			seq_printf(m, "    %-23s : \"%s\"\n", "Driver",
				   macsec_device_debug[i].drv_name);
			seq_printf(m, "    %-23s : %s\n", "State", state_str);
		}
	}

	return 0;
}

DEFINE_SHOW_ATTRIBUTE(nss_macsec_module_status);

static int nss_macsec_debugfs_init(void)
{
	macsec_debugfs_root = debugfs_create_dir("qca-nss-macsec", NULL);
	if (!macsec_debugfs_root) {
		osal_print("Failed to create debugfs root directory\n");
		return -ENOMEM;
	}

	if (!debugfs_create_file("module_state", 0444, macsec_debugfs_root,
				NULL, &nss_macsec_module_status_fops)) {
		osal_print("Failed to create module_status debugfs file\n");
		debugfs_remove_recursive(macsec_debugfs_root);
		return -ENOMEM;
	}

	return 0;
}

static void nss_macsec_debugfs_exit(void)
{
	debugfs_remove_recursive(macsec_debugfs_root);
}

static int nss_macsec_dev_event(struct notifier_block  *nb,
				 unsigned long event, void  *info)
{
	struct net_device *event_dev = netdev_notifier_info_to_dev(info);
	int ret = 0;
	u32 phyid = 0;

	/* Defensive check for event_dev */
	if (unlikely(!event_dev))
		return NOTIFY_DONE;

	if (NULL == event_dev->phydev)
		return NOTIFY_DONE;

	phyid = macsec_get_phyid(event_dev->phydev);

	switch (phyid) {
	case QCA8081_PHY:
	case QCA8084_PHY:
	case QCA8111_PHY:
	case QCE1204_PHY:
		break;
	default:
		return NOTIFY_DONE;
	}

	switch (event) {
	case NETDEV_REGISTER:
		atomic_inc(&macsec_stats.register_count);
		ret = qca_macsec_device_attach(event_dev);
		ret = ret ? NOTIFY_DONE : NOTIFY_OK;
		break;
	case NETDEV_UNREGISTER:
		atomic_inc(&macsec_stats.unregister_count);
		ret = qca_macsec_device_detach(event_dev);
		ret = ret ? NOTIFY_DONE : NOTIFY_OK;
		break;
	default:
		ret = NOTIFY_DONE;
		break;
	}

	return ret;
}

/*
 * Linux Net device Notifier
 */
static struct notifier_block nss_macsec_netdev_notifier = {
	.notifier_call = nss_macsec_dev_event,
};

static int __init nss_macsec_init(void)
{
	int ret = 0;

	/* Initialize statistics */
	memset(&macsec_device_debug, 0, sizeof(macsec_device_debug));

	/* Initialize debugfs FIRST - so we can always check status */
	ret = nss_macsec_debugfs_init();
	if (ret) {
		osal_print("Failed to initialize debugfs, error=%d\n", ret);
		/* Continue - debugfs is not critical for core functionality */
	}

	/* System resource initialization */
	ret = nss_macsec_netlink_init();
	if (ret) {
		macsec_stats.current_state = MACSEC_NETLINK_INIT_FAILURE;
		return ret;
	}

	nss_macsec_mutex_init();

	ret = register_netdevice_notifier(&nss_macsec_netdev_notifier);
	if (ret) {
		macsec_stats.current_state = MACSEC_NET_NOTIFIER_FAILURE;
		/* Cleanup resources before exit */
		nss_macsec_netlink_fini();
		nss_macsec_mutex_destroy();
		return ret;
	}

	/* Module initialization successful - set to SUCCESS state */
	macsec_stats.current_state = MACSEC_SUCCESS;
	return 0;
}

static void __exit nss_macsec_fini(void)
{
	unregister_netdevice_notifier(&nss_macsec_netdev_notifier);

	nss_macsec_netlink_fini();
	nss_macsec_debugfs_exit();
	nss_macsec_mutex_destroy();
	qca_macsec_device_cleanup();

	osal_print("nss_macsec exit success\n");
}

module_init(nss_macsec_init);
module_exit(nss_macsec_fini);
#ifdef MODULE_LICENSE
MODULE_LICENSE("Dual BSD/GPL");
#endif
