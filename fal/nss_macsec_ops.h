/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all copies.
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/**
 * @defgroup
 * @{
 */
#ifndef _NSS_MACSEC_OPS_H_
#define _NSS_MACSEC_OPS_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "qca808x_macsec.h"

#define PHY_NAPA 0x004DD100
#define MAX_SECY_ID      0x3

typedef g_error_t (*secy_init_func)(u32 secy_id);
typedef g_error_t (*secy_en_set_func)(u32 secy_id, bool enable);
typedef g_error_t (*secy_en_get_func)(u32 secy_id, bool *enable);
typedef g_error_t (*secy_mtu_get_func)(u32 secy_id, u32 *pmtu);
typedef g_error_t (*secy_mtu_set_func)(u32 secy_id, u32 mtu);
typedef g_error_t (*secy_cipher_suite_get_func)(u32 secy_id,
	enum secy_cipher_suite_t *p_cipher_suite);
typedef g_error_t (*secy_cipher_suite_set_func)(u32 secy_id,
	enum secy_cipher_suite_t cipher_suite);
typedef g_error_t (*secy_controlled_port_en_get_func)(u32 secy_id,
	bool *penable);
typedef g_error_t (*secy_controlled_port_en_set_func)(u32 secy_id,
	bool enable);
typedef g_error_t (*secy_sc_sa_mapping_mode_get_func)(u32 secy_id,
	enum secy_sc_sa_mapping_mode_t *pmode);
typedef g_error_t (*secy_sc_sa_mapping_mode_set_func)(u32 secy_id,
	enum secy_sc_sa_mapping_mode_t mode);
typedef g_error_t (*secy_xpn_en_set_func)(u32 secy_id, bool enable);
typedef g_error_t (*secy_xpn_en_get_func)(u32 secy_id, bool *enable);
typedef g_error_t (*secy_flow_control_en_set_func)(u32 secy_id, bool enable);
typedef g_error_t (*secy_flow_control_en_get_func)(u32 secy_id, bool *enable);
typedef g_error_t (*secy_special_pkt_ctrl_set_func)(u32 secy_id,
	enum secy_packet_type_t packet_type,
	enum secy_packet_action_t action);
typedef g_error_t (*secy_special_pkt_ctrl_get_func)(u32 secy_id,
	enum secy_packet_type_t packet_type,
	enum secy_packet_action_t *action);
typedef g_error_t (*secy_udf_ethtype_set_func)(u32 secy_id, bool enable,
	u16 type);
typedef g_error_t (*secy_udf_ethtype_get_func)(u32 secy_id, bool *enable,
	u16 *type);
typedef g_error_t (*secy_loopback_set_func)(u32 secy_id,
	enum secy_loopback_type_t type);
typedef g_error_t (*secy_loopback_get_func)(u32 secy_id,
	enum secy_loopback_type_t *type);

/* rx */
typedef g_error_t (*secy_rx_prc_lut_get_func)(u32 secy_id, u32 index,
	struct secy_rx_prc_lut_t *pentry);
typedef g_error_t (*secy_rx_prc_lut_set_func)(u32 secy_id, u32 index,
	struct secy_rx_prc_lut_t *pentry);
typedef g_error_t (*secy_rx_sc_create_func)(u32 secy_id, u32 channel);
typedef g_error_t (*secy_rx_sc_del_func)(u32 secy_id, u32 channel);
typedef g_error_t (*secy_rx_sc_del_all_func)(u32 secy_id);
typedef g_error_t (*secy_rx_sc_validate_frame_get_func)(u32 secy_id,
	u32 channel, enum secy_vf_t *pmode);
typedef g_error_t (*secy_rx_sc_validate_frame_set_func)(u32 secy_id,
	u32 channel, enum secy_vf_t mode);
typedef g_error_t (*secy_rx_sc_replay_protect_get_func)(u32 secy_id,
	u32 channel, bool *penable);
typedef g_error_t (*secy_rx_sc_replay_protect_set_func)(u32 secy_id,
	u32 channel, bool enable);
typedef g_error_t (*secy_rx_sc_replay_window_get_func)(u32 secy_id,
	u32 channel, u32 *pwindow);
typedef g_error_t (*secy_rx_sc_replay_window_set_func)(u32 secy_id,
	u32 channel, u32 window);
typedef g_error_t (*secy_rx_sa_create_func)(u32 secy_id, u32 channel, u32 an);
typedef g_error_t (*secy_rx_sak_get_func)(u32 secy_id, u32 channel,
	u32 an, struct secy_sak_t *pkey);
typedef g_error_t (*secy_rx_sak_set_func)(u32 secy_id, u32 channel,
	u32 an, struct secy_sak_t *pkey);
typedef g_error_t (*secy_rx_sa_en_get_func)(u32 secy_id, u32 channel,
	u32 an, bool *penable);
typedef g_error_t (*secy_rx_sa_en_set_func)(u32 secy_id, u32 channel,
	u32 an, bool enable);
typedef g_error_t (*secy_rx_sc_in_used_get_func)(u32 secy_id,
	u32 channel, bool *p_in_used);
typedef g_error_t (*secy_rx_sa_next_pn_get_func)(u32 secy_id, u32 channel,
	u32 an, u32 *pnpn);
typedef g_error_t (*secy_rx_reg_get_func)(u32 secy_id, u32 addr, u16 *pvalue);
typedef g_error_t (*secy_rx_reg_set_func)(u32 secy_id, u32 addr, u16 value);
typedef g_error_t (*secy_rx_sa_next_xpn_get_func)(u32 secy_id, u32 channel,
	u32 an, u32 *pnpn);
typedef g_error_t (*secy_rx_sa_next_xpn_set_func)(u32 secy_id, u32 channel,
	u32 an, u32 pnpn);
typedef g_error_t (*secy_rx_sc_ssci_get_func)(u32 secy_id, u32 channel,
	u32 *ssci);
typedef g_error_t (*secy_rx_sc_ssci_set_func)(u32 secy_id, u32 channel,
	u32 ssci);
typedef g_error_t (*secy_rx_sa_ki_get_func)(u32 secy_id, u32 channel, u32 an,
	struct secy_sa_ki_t *ki);
typedef g_error_t (*secy_rx_sa_ki_set_func)(u32 secy_id, u32 channel, u32 an,
	struct secy_sa_ki_t *ki);
typedef g_error_t (*secy_rx_prc_lut_clear_func)(u32 secy_id, u32 index);
typedef g_error_t (*secy_rx_prc_lut_clear_all_func)(u32 secy_id);
typedef g_error_t (*secy_rx_sa_del_func)(u32 secy_id, u32 channel, u32 an);
typedef g_error_t (*secy_rx_sa_del_all_func)(u32 secy_id);

typedef g_error_t (*secy_rx_sa_in_used_get_func)(u32 secy_id, u32 channel,
	u32 an, bool *p_in_used);
typedef g_error_t (*secy_rx_replay_protect_get_func)(u32 secy_id,
	bool *enable);
typedef g_error_t (*secy_rx_replay_protect_set_func)(u32 secy_id,
	bool enable);
typedef g_error_t (*secy_rx_validate_frame_get_func)(u32 secy_id,
	enum secy_vf_t *pmode);
typedef g_error_t (*secy_rx_validate_frame_set_func)(u32 secy_id,
	enum secy_vf_t mode);
typedef g_error_t (*secy_rx_sc_en_get_func)(u32 secy_id, u32 channel,
	bool *penable);
typedef g_error_t (*secy_rx_sc_en_set_func)(u32 secy_id, u32 channel,
	bool enable);


/* tx */

typedef g_error_t (*secy_tx_sc_in_used_get_func)(u32 secy_id, u32 channel,
bool *p_in_used);
typedef g_error_t (*secy_tx_sc_tci_7_2_get_func)(u32 secy_id, u32 channel,
	u8 *ptci);
typedef g_error_t (*secy_tx_sc_tci_7_2_set_func)(u32 secy_id, u32 channel,
	u8 tci);
typedef g_error_t (*secy_tx_sc_create_func)(u32 secy_id, u32 channel,
	u8 *psci, u32 sci_len);
typedef g_error_t (*secy_tx_sc_sci_get_func)(u32 secy_id, u32 channel,
	u8 *psci, u32 sci_len);
typedef g_error_t (*secy_tx_sa_en_get_func)(u32 secy_id, u32 channel, u32 an,
	bool *penable);
typedef g_error_t (*secy_tx_sa_en_set_func)(u32 secy_id, u32 channel, u32 an,
	bool enable);
typedef g_error_t (*secy_tx_sa_next_pn_get_func)(u32 secy_id, u32 channel,
	u32 an, u32 *p_next_pn);
typedef g_error_t (*secy_tx_sa_next_pn_set_func)(u32 secy_id, u32 channel,
	u32 an, u32 next_pn);
typedef g_error_t (*secy_tx_sc_an_get_func)(u32 secy_id, u32 channel,
	u32 *pan);
typedef g_error_t (*secy_tx_sc_an_set_func)(u32 secy_id, u32 channel, u32 an);
typedef g_error_t (*secy_tx_sc_del_func)(u32 secy_id, u32 channel);
typedef g_error_t (*secy_tx_sc_del_all_func)(u32 secy_id);
typedef g_error_t (*secy_tx_sc_offset_get_func)(u32 secy_id,
	u32 channel, enum secy_cofidentiality_offset_t *offset);
typedef g_error_t (*secy_tx_sc_offset_set_func)(u32 secy_id,
	u32 channel, enum secy_cofidentiality_offset_t offset);
typedef g_error_t (*secy_tx_class_lut_get_func)(u32 secy_id, u32 index,
	struct secy_tx_class_lut_t *pentry);
typedef g_error_t (*secy_tx_class_lut_set_func)(u32 secy_id, u32 index,
	struct secy_tx_class_lut_t *pentry);

typedef g_error_t (*secy_tx_sak_get_func)(u32 secy_id, u32 channel,
	u32 an, struct secy_sak_t *pentry);
typedef g_error_t (*secy_tx_sak_set_func)(u32 secy_id, u32 channel,
	u32 an, struct secy_sak_t *pentry);
typedef g_error_t (*secy_tx_sc_protect_get_func)(u32 secy_id, u32 channel,
	bool *penable);
typedef g_error_t (*secy_tx_sc_protect_set_func)(u32 secy_id, u32 channel,
	bool enable);
typedef g_error_t (*secy_tx_reg_get_func)(u32 secy_id, u32 addr, u16 *pvalue);
typedef g_error_t (*secy_tx_reg_set_func)(u32 secy_id, u32 addr, u16 value);
typedef g_error_t (*secy_tx_sa_next_xpn_get_func)(u32 secy_id, u32 channel,
	u32 an, u32 *pnpn);
typedef g_error_t (*secy_tx_sa_next_xpn_set_func)(u32 secy_id, u32 channel,
	u32 an, u32 pnpn);
typedef g_error_t (*secy_tx_sc_ssci_get_func)(u32 secy_id, u32 channel,
	u32 *ssci);
typedef g_error_t (*secy_tx_sc_ssci_set_func)(u32 secy_id, u32 channel,
	u32 ssci);
typedef g_error_t (*secy_tx_sa_ki_get_func)(u32 secy_id, u32 channel, u32 an,
	struct secy_sa_ki_t *ki);
typedef g_error_t (*secy_tx_sa_ki_set_func)(u32 secy_id, u32 channel, u32 an,
	struct secy_sa_ki_t *ki);
typedef g_error_t (*secy_tx_class_lut_clear_func)(u32 secy_id, u32 index);
typedef g_error_t (*secy_tx_class_lut_clear_all_func)(u32 secy_id);
typedef g_error_t (*secy_tx_sa_create_func)(u32 secy_id, u32 channel, u32 an);
typedef g_error_t (*secy_tx_sa_del_func)(u32 secy_id, u32 channel, u32 an);
typedef g_error_t (*secy_tx_sa_del_all_func)(u32 secy_id);
typedef g_error_t (*secy_tx_sa_in_used_get_func)(u32 secy_id, u32 channel,
	u32 an, bool *p_in_used);
typedef g_error_t (*secy_tx_sc_en_get_func)(u32 secy_id, u32 channel,
	bool *penable);
typedef g_error_t (*secy_tx_sc_en_set_func)(u32 secy_id, u32 channel,
	bool enable);
typedef g_error_t (*secy_tx_class_lut_sci_update_func)(u32 secy_id,
	u32 channel, u8 *sci);


/*mib */

typedef g_error_t (*secy_tx_sa_mib_get_func)(u32 secy_id, u32 channel, u32 an,
	struct secy_tx_sa_mib_t *pmib);
typedef g_error_t (*secy_tx_sc_mib_get_func)(u32 secy_id, u32 channel,
	struct secy_tx_sc_mib_t *pmib);
typedef g_error_t (*secy_tx_mib_get_func)(u32 secy_id,
	struct secy_tx_mib_t *pmib);
typedef g_error_t (*secy_rx_sa_mib_get_func)(u32 secy_id, u32 channel, u32 an,
	struct secy_rx_sa_mib_t *pmib);
typedef g_error_t (*secy_rx_mib_get_func)(u32 secy_id,
	struct secy_rx_mib_t *pmib);
typedef g_error_t (*secy_tx_sa_mib_clear_func)(u32 secy_id, u32 channel,
	u32 an);
typedef g_error_t (*secy_tx_sc_mib_clear_func)(u32 secy_id, u32 channel);
typedef g_error_t (*secy_tx_mib_clear_func)(u32 secy_id);
typedef g_error_t (*secy_rx_sa_mib_clear_func)(u32 secy_id, u32 channel,
	u32 an);
typedef g_error_t (*secy_rx_mib_clear_func)(u32 secy_id);

/*filter*/
typedef g_error_t (*secy_tx_udf_ufilt_cfg_set_func)(u32 secy_id,
	struct secy_udf_filt_cfg_t *cfg);
typedef g_error_t (*secy_tx_udf_ufilt_cfg_get_func)(u32 secy_id,
	struct secy_udf_filt_cfg_t *cfg);
typedef g_error_t (*secy_tx_udf_cfilt_cfg_set_func)(u32 secy_id,
	struct secy_udf_filt_cfg_t *cfg);
typedef g_error_t (*secy_tx_udf_cfilt_cfg_get_func)(u32 secy_id,
	struct secy_udf_filt_cfg_t *cfg);
typedef g_error_t (*secy_rx_udf_ufilt_cfg_set_func)(u32 secy_id,
	struct secy_udf_filt_cfg_t *cfg);
typedef g_error_t (*secy_rx_udf_ufilt_cfg_get_func)(u32 secy_id,
	struct secy_udf_filt_cfg_t *cfg);
typedef g_error_t (*secy_rx_udf_filt_set_func)(u32 secy_id, u32 index,
	struct secy_udf_filt_t *filter);
typedef g_error_t (*secy_rx_udf_filt_get_func)(u32 secy_id, u32 index,
	struct secy_udf_filt_t *filter);
typedef g_error_t (*secy_tx_udf_filt_set_func)(u32 secy_id, u32 index,
	struct secy_udf_filt_t *filter);
typedef g_error_t (*secy_tx_udf_filt_get_func)(u32 secy_id, u32 index,
	struct secy_udf_filt_t *filter);

struct secy_drv_t {
	secy_init_func secy_init;
	secy_controlled_port_en_get_func secy_controlled_port_en_get;
	secy_controlled_port_en_set_func secy_controlled_port_en_set;
	secy_cipher_suite_get_func secy_cipher_suite_get;
	secy_cipher_suite_set_func secy_cipher_suite_set;
	secy_mtu_get_func secy_mtu_get;
	secy_mtu_set_func secy_mtu_set;
	secy_en_set_func secy_en_set;
	secy_en_get_func secy_en_get;
	secy_sc_sa_mapping_mode_set_func secy_sc_sa_mapping_mode_set;
	secy_sc_sa_mapping_mode_get_func secy_sc_sa_mapping_mode_get;
	secy_xpn_en_set_func secy_xpn_en_set;
	secy_xpn_en_get_func secy_xpn_en_get;
	secy_flow_control_en_set_func secy_flow_control_en_set;
	secy_flow_control_en_get_func secy_flow_control_en_get;
	secy_special_pkt_ctrl_set_func secy_special_pkt_ctrl_set;
	secy_special_pkt_ctrl_get_func secy_special_pkt_ctrl_get;
	secy_udf_ethtype_set_func secy_udf_ethtype_set;
	secy_udf_ethtype_get_func secy_udf_ethtype_get;
	secy_loopback_set_func secy_loopback_set;
	secy_loopback_get_func secy_loopback_get;


	/*rx */
	secy_rx_prc_lut_get_func secy_rx_prc_lut_get;
	secy_rx_prc_lut_set_func secy_rx_prc_lut_set;
	secy_rx_sc_create_func secy_rx_sc_create;
	secy_rx_sc_del_func secy_rx_sc_del;
	secy_rx_sc_del_all_func secy_rx_sc_del_all;
	secy_rx_sc_validate_frame_get_func secy_rx_sc_validate_frame_get;
	secy_rx_sc_validate_frame_set_func secy_rx_sc_validate_frame_set;
	secy_rx_sc_replay_protect_get_func secy_rx_sc_replay_protect_get;
	secy_rx_sc_replay_protect_set_func secy_rx_sc_replay_protect_set;
	secy_rx_sc_replay_window_get_func secy_rx_sc_anti_replay_window_get;
	secy_rx_sc_replay_window_set_func secy_rx_sc_anti_replay_window_set;
	secy_rx_sa_create_func secy_rx_sa_create;
	secy_rx_sak_get_func secy_rx_sak_get;
	secy_rx_sak_set_func secy_rx_sak_set;
	secy_rx_sa_en_get_func secy_rx_sa_en_get;
	secy_rx_sa_en_set_func secy_rx_sa_en_set;
	secy_rx_sa_next_pn_get_func secy_rx_sa_next_pn_get;
	secy_rx_sc_in_used_get_func secy_rx_sc_in_used_get;
	secy_rx_reg_get_func secy_rx_reg_get;
	secy_rx_reg_set_func secy_rx_reg_set;
	secy_rx_sa_next_xpn_set_func secy_rx_sa_next_xpn_set;
	secy_rx_sa_next_xpn_get_func secy_rx_sa_next_xpn_get;
	secy_rx_sc_ssci_set_func secy_rx_sc_ssci_set;
	secy_rx_sc_ssci_get_func secy_rx_sc_ssci_get;
	secy_rx_sa_ki_set_func secy_rx_sa_ki_set;
	secy_rx_sa_ki_get_func secy_rx_sa_ki_get;
	secy_rx_prc_lut_clear_func secy_rx_prc_lut_clear;
	secy_rx_prc_lut_clear_all_func secy_rx_prc_lut_clear_all;
	secy_rx_sa_in_used_get_func secy_rx_sa_in_used_get;
	secy_rx_replay_protect_get_func secy_rx_replay_protect_get;
	secy_rx_replay_protect_set_func secy_rx_replay_protect_set;
	secy_rx_validate_frame_get_func secy_rx_validate_frame_get;
	secy_rx_validate_frame_set_func secy_rx_validate_frame_set;
	secy_rx_sc_en_get_func secy_rx_sc_en_get;
	secy_rx_sc_en_set_func secy_rx_sc_en_set;
	secy_rx_sa_del_func secy_rx_sa_del;
	secy_rx_sa_del_all_func secy_rx_sa_del_all;

	/*tx*/
	secy_tx_sc_in_used_get_func secy_tx_sc_in_used_get;
	secy_tx_sc_tci_7_2_get_func secy_tx_sc_tci_7_2_get;
	secy_tx_sc_tci_7_2_set_func secy_tx_sc_tci_7_2_set;
	secy_tx_sa_next_pn_get_func secy_tx_sa_next_pn_get;
	secy_tx_sa_next_pn_set_func secy_tx_sa_next_pn_set;
	secy_tx_sc_an_get_func secy_tx_sc_an_get;
	secy_tx_sc_an_set_func secy_tx_sc_an_set;
	secy_tx_sa_en_get_func secy_tx_sa_en_get;
	secy_tx_sa_en_set_func secy_tx_sa_en_set;
	secy_tx_sc_create_func secy_tx_sc_create;
	secy_tx_sc_sci_get_func secy_tx_sc_sci_get;
	secy_tx_sc_del_func secy_tx_sc_del;
	secy_tx_sc_del_all_func secy_tx_sc_del_all;
	secy_tx_sc_offset_get_func secy_tx_sc_confidentiality_offset_get;
	secy_tx_sc_offset_set_func secy_tx_sc_confidentiality_offset_set;
	secy_tx_class_lut_get_func secy_tx_class_lut_get;
	secy_tx_class_lut_set_func secy_tx_class_lut_set;
	secy_tx_sak_get_func secy_tx_sak_get;
	secy_tx_sak_set_func secy_tx_sak_set;
	secy_tx_sc_protect_get_func secy_tx_sc_protect_get;
	secy_tx_sc_protect_set_func secy_tx_sc_protect_set;
	secy_tx_reg_get_func secy_tx_reg_get;
	secy_tx_reg_set_func secy_tx_reg_set;
	secy_tx_sa_next_xpn_set_func secy_tx_sa_next_xpn_set;
	secy_tx_sa_next_xpn_get_func secy_tx_sa_next_xpn_get;
	secy_tx_sc_ssci_set_func secy_tx_sc_ssci_set;
	secy_tx_sc_ssci_get_func secy_tx_sc_ssci_get;
	secy_tx_sa_ki_set_func secy_tx_sa_ki_set;
	secy_tx_sa_ki_get_func secy_tx_sa_ki_get;
	secy_tx_class_lut_clear_func secy_tx_class_lut_clear;
	secy_tx_class_lut_clear_all_func secy_tx_class_lut_clear_all;
	secy_tx_sa_create_func secy_tx_sa_create;
	secy_tx_sa_del_func secy_tx_sa_del;
	secy_tx_sa_del_all_func secy_tx_sa_del_all;
	secy_tx_sa_in_used_get_func secy_tx_sa_in_used_get;
	secy_tx_sc_en_get_func secy_tx_sc_en_get;
	secy_tx_sc_en_set_func secy_tx_sc_en_set;
	secy_tx_class_lut_sci_update_func secy_tx_class_lut_sci_update;

	/*mib*/
	secy_tx_sa_mib_get_func secy_tx_sa_mib_get;
	secy_tx_sc_mib_get_func secy_tx_sc_mib_get;
	secy_tx_mib_get_func secy_tx_mib_get;
	secy_rx_sa_mib_get_func secy_rx_sa_mib_get;
	secy_rx_mib_get_func secy_rx_mib_get;
	secy_tx_sa_mib_clear_func secy_tx_sa_mib_clear;
	secy_tx_sc_mib_clear_func secy_tx_sc_mib_clear;
	secy_tx_mib_clear_func secy_tx_mib_clear;
	secy_rx_sa_mib_clear_func secy_rx_sa_mib_clear;
	secy_rx_mib_clear_func secy_rx_mib_clear;

	secy_tx_udf_ufilt_cfg_set_func secy_tx_udf_ufilt_cfg_set;
	secy_tx_udf_ufilt_cfg_get_func secy_tx_udf_ufilt_cfg_get;
	secy_tx_udf_cfilt_cfg_set_func secy_tx_udf_cfilt_cfg_set;
	secy_tx_udf_cfilt_cfg_get_func secy_tx_udf_cfilt_cfg_get;
	secy_rx_udf_ufilt_cfg_set_func secy_rx_udf_ufilt_cfg_set;
	secy_rx_udf_ufilt_cfg_get_func secy_rx_udf_ufilt_cfg_get;
	secy_rx_udf_filt_set_func secy_rx_udf_filt_set;
	secy_rx_udf_filt_get_func secy_rx_udf_filt_get;
	secy_tx_udf_filt_set_func secy_tx_udf_filt_set;
	secy_tx_udf_filt_get_func secy_tx_udf_filt_get;
};

enum secy_phy_type_t {
	NAPA_PHY_CHIP = 0,
	MAX_PHY_CHIP,
};

struct secy_driver_instance_t {
	enum secy_phy_type_t secy_phy_type;
	struct secy_drv_t *secy_ops;
	int (*init)(u32 secy_id);
	int (*exit)(u32 secy_id);
};

struct secy_info_t {
	u32 phy_addr;
	enum secy_phy_type_t secy_phy_type;
};

g_error_t secy_ops_init(enum secy_phy_type_t phy_type);

g_error_t secy_ops_register(enum secy_phy_type_t phy_type,
	struct secy_drv_t *secy_ops);

struct secy_drv_t *nss_macsec_secy_ops_get(u32 secy_id);

void nss_macsec_secy_info_set(u32 secy_id, u32 phy_addr);

u32 secy_id_to_phy_addr(u32 secy_id);

int nss_macsec_secy_driver_init(u32 secy_id);

g_error_t nss_macsec_secy_driver_cleanup(u32 secy_id);

g_error_t secy_ops_unregister(enum secy_phy_type_t phy_type);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif


