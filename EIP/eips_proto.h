/*
 *            Copyright (c) 2002-2009 by Real Time Automation, Inc.
 *
 *  This software is copyrighted by and is the sole property of
 *  Real Time Automation, Inc. (RTA).  All rights, title, ownership, 
 *  or other interests in the software remain the property of RTA.  
 *  This software may only be used in accordance with the corresponding
 *  license agreement.  Any unauthorized use, duplication, transmission,
 *  distribution, or disclosure of this software is expressly forbidden.
 *
 *  This Copyright notice MAY NOT be removed or modified without prior
 *  written consent of RTA.
 *
 *  RTA reserves the right to modify this software without notice.
 *
 *  Real Time Automation
 *  150 S. Sunny Slope Road            USA 262.439.4999
 *  Suite 130                          http://www.rtaautomation.com
 *  Brookfield, WI 53005               software@rtaautomation.com
 *
 *************************************************************************
 *
 *    Version Date: 12/16/2009
 *         Version: 2.14
 *    Conformed To: EtherNet/IP Protocol Conformance Test A-7 (17-AUG-2009)
 *     Module Name: eips_proto.h
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * =======================================================================
 * This file contains EtherNet/IP Server funcion prototypes.
 *
 */

#ifndef __EIPS_PROTO_H__
#define __EIPS_PROTO_H__

/* ******************************* */
/* Global Functions in eips_cco.c */
/* ******************************* */
#ifdef EIPC_CCO_USED
    void eipc_cco_init (uint8 init_type);
	void eipc_cco_objModProc (uint16 classid, uint16 instid, uint8 attrid, uint8 servcode, EIPS_USER_MSGRTR_REQ_FMT *request);  
	void eipc_cco_state_changed (uint16 server_handle, uint8 ucmm_server_state);
	void eipc_cco_process (void);
	void eipc_cco_io_state_changed (uint16 server_handle, uint8 io_server_state);
	void eipc_cco_io_newConsumeData (uint16 server_handle, uint8 cnxn_id);
#endif

/* ******************************* */
/* Global Functions in eips_pccc.c */
/* ******************************* */
#ifdef EIPS_PCCC_USED /* OPTIONAL */
    void eips_pccc_init (uint8 init_type);
    void eips_pccc_execute (CPF_MESSAGE_STRUCT *);
    void eips_pccc_build_error (uint8 gen_stat, uint16 ext_stat_size, uint16 * ext_stat);

    /* allow the user to dynamically change which integer (N) registers are used */
    int8 eips_userobj_read_B_reg_pccc   (uint16 file_num, uint16 file_offset, uint16 length, uint16 *reg_data);
    int8 eips_userobj_read_N_reg_pccc   (uint16 file_num, uint16 file_offset, uint16 length, uint16 *reg_data);
    int8 eips_userobj_read_F_reg_pccc   (uint16 file_num, uint16 file_offset, uint16 length, float  *reg_data);
    int8 eips_userobj_read_ST_reg_pccc  (uint16 file_num, uint16 file_offset, uint16 length, EIPS_PCCC_STRING_TYPE *reg_data);

    int8 eips_userobj_write_B_reg_pccc  (uint16 file_num, uint16 file_offset, uint16 length, uint16 *reg_data);
    int8 eips_userobj_write_N_reg_pccc  (uint16 file_num, uint16 file_offset, uint16 length, uint16 *reg_data);
    int8 eips_userobj_write_F_reg_pccc  (uint16 file_num, uint16 file_offset, uint16 length, float  *reg_data);
    int8 eips_userobj_write_ST_reg_pccc (uint16 file_num, uint16 file_offset, uint16 length, EIPS_PCCC_STRING_TYPE *reg_data);
#endif

/* *********************************** */
/* Global Functions in eips_userdf1.c  */
/* *********************************** */
#ifdef EIPS_PCCC_USED /* OPTIONAL */
    void   eips_userdf1_init (uint8 init_type);
    uint16 eips_userdf1_proc_msg (uint8 * req_msg, uint16 req_msg_size, uint8 * rsp_msg, uint16 max_rsp_msg_size);
#endif

/* ******************************* */
/* Global Functions in eips_cnxn.c */
/* ******************************* */
void eips_cnxn_init	 (uint8 init_type);
void eips_cnxn_free	 (EIPS_CONNECTION_DATA_STRUCT *cnxnptr);
void eips_cnxn_Process	 (void);
void eips_cnxn_fwdOpen	 (CPF_MESSAGE_STRUCT *);
void eips_cnxn_fwdClose  (CPF_MESSAGE_STRUCT *);
void eips_cnxn_emTimeout (uint16 timer_num);
void eips_cnxn_errorFwdOpen  (EIPS_CONNECTION_DATA_STRUCT *temp_cnxn, CPF_MESSAGE_STRUCT *cpf);
void eips_cnxn_validFwdOpen  (EIPS_CONNECTION_DATA_STRUCT *temp_cnxn, CPF_MESSAGE_STRUCT *cpf);
void eips_cnxn_errorFwdClose (EIPS_CONNECTION_DATA_STRUCT *temp_cnxn, CPF_MESSAGE_STRUCT *cpf);
void eips_cnxn_validFwdClose (EIPS_CONNECTION_DATA_STRUCT *temp_cnxn, CPF_MESSAGE_STRUCT *cpf);
void eips_cnxn_structInit    (EIPS_CONNECTION_DATA_STRUCT *temp_cnxn); /* used to free connection */
void eips_cnxn_structCopy (EIPS_CONNECTION_DATA_STRUCT *dst_cnxnptr, EIPS_CONNECTION_DATA_STRUCT *src_cnxnptr);
EIPS_CONNECTION_DATA_STRUCT * eips_cnxn_getUnusedCnxn(void);
uint16 eips_cnxn_getCnxnTmoMult (uint8);
uint32 eips_cnxn_getConnectionID (void);
uint32 EIPS_APIROUND (uint32 old_val);
uint32 EIPS_APITICKS (uint32 api);
void eips_cnxn_timeout (void); /* called when any connection times out (for LED processing) */

/* ****************************** */
/* Global Functions in eips_cpf.c */
/* ****************************** */
void   eips_cpf_init		    (uint8 init_type);
void   eips_cpf_ProcessCPF	    (EIPS_ENCAP_MSG_STRUCT *EncapReq, EIPS_SOCKET_STRUCT *sock);
uint8  eips_cpf_o2tCnxnPtValid	(uint8);
uint8  eips_cpf_t2oCnxnPtValid	(uint8);
int16  eips_cpf_getAsmSize	    (uint16 instance);
uint8  eips_cpf_asmInstExists   (uint16 instance);

/* ******************************** */
/* Global Functions in eips_encap.c */
/* ******************************** */
void   eips_encap_init (uint8 init_type);
uint16 eips_encap_process (EIPS_SOCKET_STRUCT *sock, uint8 *msg, uint16 msg_siz);
void   eips_encap_freeSessionIx (EIPS_USERSYS_SOCKTYPE socket_id);
void   eips_encap_unSupEncapMsg (EIPS_ENCAP_MSG_STRUCT *EncapReq, EIPS_SOCKET_STRUCT *sock);
EIPS_SESSION_STRUCT * eips_encap_getSessionStruct (uint32 sessionID);

/* ******************************** */
/* Global Functions in eips_iomsg.c */
/* ******************************** */
void   eips_iomsg_init              (uint8 init_type);
void   eips_iomsg_process           (void);
uint16 eips_iomsg_proc_o2t_iomsg    (uint32 ipaddr, uint8 *msg, uint16 msg_siz);
void   eips_iomsg_open              (CPF_MESSAGE_STRUCT *cpf, EIPS_CONNECTION_DATA_STRUCT *temp_cnxn);
uint8  eips_iomsg_close             (EIPS_CONNECTION_DATA_STRUCT *temp_cnxn);
uint8  eips_iomsg_allocated         (uint16 o2t_inst_id);
uint8  eips_iomsg_outputs_valid     (uint16 o2t_inst_id);
void   eips_iomsg_t2o_cos           (uint16 t2o_inst_id);
uint8  eips_iomsg_ValidMulticastAddr(uint32 addr);

/* ********************************* */
/* Global Functions in eips_rtasys.c */
/* ********************************* */
void eips_rtasys_init	     (void);
void eips_rtasys_process     (uint32 ticks_passed_since_last_call);
void eips_rtasys_setState    (EIPS_USERSYS_SOCKTYPE socket_id, uint8 new_state);
void eips_rtasys_onTCPAccept (EIPS_USERSYS_SOCKTYPE socket_id);
void eips_rtasys_onTCPData   (EIPS_USERSYS_SOCKTYPE socket_id, uint8 * socket_data, uint16 socket_data_size);
void eips_rtasys_onUDPData   (uint32 src_addr, uint16 src_port, uint8 * socket_data, uint16 socket_data_size);
void eips_rtasys_onTCPSent   (EIPS_USERSYS_SOCKTYPE socket_id);
void eips_rtasys_onTCPClose  (EIPS_USERSYS_SOCKTYPE socket_id);
void eips_rtasys_onIOData    (uint32 src_addr, uint8 * socket_data, uint16 socket_data_size);

/* ******************************** */
/* Global Functions in eips_timer.c */
/* ******************************** */
void    eips_timer_init	    (uint8 init_type);
void    eips_timer_process  (uint32 time_passed_in_ticks);
uint16  eips_timer_new	    (void);
void    eips_timer_free	    (uint16 timer_num);
void    eips_timer_reset    (uint16 timer_num);
void    eips_timer_newval   (uint16 timer_num, uint32 newval);
void    eips_timer_start    (uint16 timer_num);
void    eips_timer_stop     (uint16 timer_num);
uint8   eips_timer_running  (uint16 timer_num);

void    eips_timer_changeValues (uint16 timer_num, uint32 current, uint32 reload);
EIPS_TIMER_DATA_STRUCT * eips_timer_get_struct (uint16 timer_num);

/* ********************************** */
/* Global Functions in eips_userobj.c */
/* ********************************** */
void	eips_userobj_init    (uint8 init_type);
uint8	eips_userobj_procVendSpecObject (EIPS_USER_MSGRTR_REQ_FMT *, EIPS_USER_MSGRTR_RSP_FMT *);
uint32  eips_userobj_getSerialNumber (void);
void    eips_userobj_process (void);
uint8   eips_userobj_cfg_asm_process(uint16 cfg_inst_id, uint8 * config_data, uint16 config_data_size_in_bytes, uint8 *err_rsp_code, uint16 *add_err_rsp_code);

/* make the assembly processing dynamic at startup (return number of used instances) */
uint16  eips_userobj_asmGetO2TInstList (uint16 *list_ptr, uint16 max_num_inst);
uint16  eips_userobj_asmGetT2OInstList (uint16 *list_ptr, uint16 max_num_inst);

#if EIPS_USEROBJ_ASM_ELEMENT_SIZE == 4      /* DWORDS */
    void eips_userobj_asmDataWrote (uint16 inst_id, uint16 dwords_written);   
#elif EIPS_USEROBJ_ASM_ELEMENT_SIZE == 2    /* WORDS */
    void eips_userobj_asmDataWrote (uint16 inst_id, uint16 words_written);   
#else                                       /* BYTES */
    void eips_userobj_asmDataWrote (uint16 inst_id, uint16 bytes_written);   
#endif

#if EIPS_USEROBJ_ASM_ELEMENT_SIZE == 4      /* DWORDS */
   uint32 * eips_userobj_getAsmPtr (uint16 inst_id, uint16 *size_in_dwords);
#elif EIPS_USEROBJ_ASM_ELEMENT_SIZE == 2    /* WORDS */
   uint16 * eips_userobj_getAsmPtr (uint16 inst_id, uint16 *size_in_words);
#else                                       /* BYTES */
   uint8  * eips_userobj_getAsmPtr (uint16 inst_id, uint16 *size_in_bytes);
#endif

/* *********************************** */
/* Global Functions in eips_usersock.c */
/* *********************************** */
void   eips_usersock_init     (uint8 init_type);
void   eips_usersock_process  (void);
void   eips_usersock_sendTCPData (EIPS_USERSYS_SOCKTYPE socket_id, uint8 * socket_data, uint16 socket_data_size);
void   eips_usersock_sendUDPData (uint32 ipaddr, uint16 port, uint8 * socket_data, uint16 socket_data_size);
void   eips_usersock_sendIOMessage (uint32 ipaddr, uint8 *resp_msg, int16 resp_msg_siz);
void   eips_usersock_tcpClose (EIPS_USERSYS_SOCKTYPE socket_id);
uint32 eips_usersock_getSockInfo_sin_addr   (EIPS_USERSYS_SOCKTYPE socket_id);
uint32 eips_usersock_getOurIPAddr	  (void);

/* ------------- */
/* TCP/IP Object */
/* ------------- */
/* get attribute parameters */
uint8 eips_usersock_getTCPObj_Attr01_Status     (uint32 *data);
uint8 eips_usersock_getTCPObj_Attr02_CfgCap     (uint32 *data);
uint8 eips_usersock_getTCPObj_Attr03_CfgCtrl    (uint32 *data);
uint8 eips_usersock_getTCPObj_Attr04_PhyLinkObj (EIPS_PHY_LINK_STRUCT *data);
uint8 eips_usersock_getTCPObj_Attr05_IntfCfg    (EIPS_IPADDR_STRUCT *data);
uint8 eips_usersock_getTCPObj_Attr06_HostName   (EIPS_TCPOBJ_BUF_STRUCT *data);

/* set attribute parameters */
uint8 eips_usersock_setTCPObj_Attr03_CfgCtrl    (uint32 *data);
uint8 eips_usersock_setTCPObj_Attr05_IntfCfg    (EIPS_IPADDR_STRUCT *data);
uint8 eips_usersock_setTCPObj_Attr06_HostName   (EIPS_TCPOBJ_BUF_STRUCT *data);

/* -------------------- */
/* Ethernet Link Object */
/* -------------------- */

/* get attribute parameters */
uint8 eips_usersock_getEthLinkObj_Attr01_IntfSpeed  (uint32 *data);
uint8 eips_usersock_getEthLinkObj_Attr02_IntfFlags  (uint32 *data);
uint8 eips_usersock_getEthLinkObj_Attr03_MacAddr    (uint8  *madid_6byte_string);
uint8 eips_usersock_getEthLinkObj_Attr04_IntfCnts   (EIPS_ELINKOBJ_INTFCNTS_STRUCT *data);
uint8 eips_usersock_getEthLinkObj_Attr05_MediaCnts  (EIPS_ELINKOBJ_MEDIACNTS_STRUCT *data);
uint8 eips_usersock_getEthLinkObj_Attr06_IntfCtrl   (EIPS_ELINKOBJ_INTFCTRL_STRUCT *data);

/* set attribute parameters */
uint8 eips_usersock_setEthLinkObj_Attr06_IntfCtrl   (EIPS_ELINKOBJ_INTFCTRL_STRUCT *data);

/* ********************************** */
/* Global Functions in eips_usersys.c */
/* ********************************** */
void    eips_usersys_init       (uint8 init_type);
void    eips_usersys_process    (void);
void    eips_usersys_fatalError (char *function_name, int16 error_num);
uint16  eips_usersys_getIncarnationID (void); 
void    eips_usersys_ledTest   (void);
  
#ifdef EIPS_IO_LED_USED
    void eips_usersys_ioLedUpdate (uint8 led_state);
#endif

#ifdef EIPS_NTWK_LED_USED
    void eips_usersys_nsLedUpdate (uint8 led_state);
#endif

/* ************************************************************ */
/*                  UTILITY FUNCTION PROTOTYPES                 */
/* ************************************************************ */
#if 1
void   rta_PutBigEndian16    (uint16 value, uint8 *pos);
void   rta_PutBigEndian32    (uint32 value, uint8 *pos);
void   rta_PutLitEndian16    (uint16 value, uint8 *pos);
void   rta_PutLitEndian32    (uint32 value, uint8 *pos);
void   rta_PutLitEndianFloat (float value, uint8 *pos);

uint16 rta_GetBigEndian16    (uint8 *pos);
uint32 rta_GetBigEndian32    (uint8 *pos);
uint16 rta_GetLitEndian16    (uint8 *pos);
uint32 rta_GetLitEndian32    (uint8 *pos);
float  rta_GetLitEndianFloat (uint8 *pos);

void   rta_ByteMove       (uint8 *dst, uint8 *src, uint16 len);
uint32 rta_Swap32 (uint32 passed_val);
#endif

#endif /* __EIPS_PROTO_H__ */
