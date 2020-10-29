
/*******************************************************************************

   (C) Copyright 2009 RAE Systems Inc.   All rights reserved

----------------- File Information ---------------------------------------------
       File Name: RCS.h
     Description: Common definitions for RCS.

---------------- Important Notes -----------------------------------------------


----------------- Rivision History ---------------------------------------------
         Version: V1.00
          Author: Alven Lu
Last Modify Date: 12/21/2006
     Description: Initial version

         Version: V1.10
          Author: Alven Lu
Last Modify Date: 12/20/2007
     Description: Change for Ver=0x61

         Version: V2.00
          Author: Alven Lu
Last Modify Date: 3/13/2009
     Description: Revised totally, try to support all version code.

*******************************************************************************/



#ifndef __RCS_H__
#define __RCS_H__
#include "./../Comm/TypeDef.h"

#define RCS_CMD_REV1          0x1
#define RCS_CMD_REV2          0x2
#define RCS_CMD_REV3          0x3
#define RCS_CMD_REV4          0x4
#define RCS_CMD_REV5          0x5
#define RCS_CMD_REV6          0x6

typedef enum {
    HOST_SEND,
    HOST_RECV,
    SLAVE_SEND,
} RCS_ROLE;

typedef enum {
    _RCS_SOP,
    _RCS_VER,
    _RCS_LEN_MSB,
    _RCS_LEN_LSB,
    _RCS_INDEX_MSB,
    _RCS_INDEX_LSB,
    _RCS_DST_MSB,
    _RCS_DST_LSB,
    _RCS_SRC_MSB,
    _RCS_SRC_LSB,
    _RCS_CMD1,
    _RCS_CMD2,
    _RCS_CMDREV,
    _RCS_DATA,
    _RCS_CHK,
    _RCS_CRCH,
    _RCS_CRCL,
    _RCS_EOP,
} RCS_STATE;

typedef enum {
    _CHECKSUM8,
    _CRC16,
} CHECK_PATTERN;

typedef struct {
    INT8U PF_REPEAT         : 1;
    INT8U PF_REPEATED       : 1;
    INT8U                   : 1;
    INT8U PF_NORESP         : 1;
    INT8U PF_BROADCAST      : 1;
    INT8U PF_ACTION         : 1;
    INT8U PF_SPECIAL        : 1;
    INT8U PF_INIT           : 1;
} __pktFlag_bits;


typedef struct {
    INT8U                   : 1;
    INT8U                   : 1;
    INT8U                   : 1;
    INT8U                   : 1;
    INT8U CS_ERR_BUSY       : 1;
    INT8U CS_ERR_DATA       : 1;
    INT8U CS_ERR_CMD        : 1;
    INT8U                   : 1;
} __commStatus_bits;


typedef struct {
    INT8U Ver;
    INT8U Valid; //true or false
    INT8U ChkPattern;
    //A package: SOP Ver Len Dest Src Cmd Data Chk EOP
    INT8U SOPLen;
    INT8U VerLen;
    INT8U LenLen;
    INT8U IndexLen;
    INT8U DestLen;
    INT8U SrcLen;
    INT8U CmdLen;
    INT8U CmdRevLen;
    INT16U DataLen;
    INT8U ChkLen;
    INT8U EOPLen;
} RCS_Pattern;


typedef struct _RCS {
    /* RCS internal use only */
    INT32S                  fd;
    RCS_STATE               StateStep;
    INT8U                   InitPac;
    INT16U                  DataIndex;
    INT8U                   InByte;
    INT16U                  PktIndex;
    INT16U                  DestAddr;
    INT16U                  SrcAddr;
    INT16U                  PktLen;
    INT8U                   CheckSum;
    INT16U                  CRC16;

    /* User accessible */
    INT8U_BIT(PacketFlags, __pktFlag_bits);
    INT8U_BIT(CommStatus, __commStatus_bits);
    RCS_Pattern           *PktCfg;
    INT16U                  Cmd;
    INT8U                   CmdRev;
    INT8U                   CmdVer;
    INT16U                  DataLen;
    INT16U                  RespLen;
    INT8U                   RtnCode;

    /* User initialized on allocation must */
    RCS_ROLE                Role;
    INT8U                   VerPac;
    INT16U                  SlaveAddr;
    INT16U                  HostAddr;
    INT16U                  DataBufLen;
    INT16U                  RespBufLen;
    INT8U                  *DataBuf;
    INT8U                  *RespBuf;
    PFNCT                pf_FuncPut;
    void                   *CmdTable;
    INT16U                  CmdTotal;
} RCS_t;

#define P2P_t RCS_t


typedef void (*PFNCT_RCS)(RCS_t *);

typedef struct {
    INT16U u16_Code;
    INT8U  u8_CmdRev;
    INT8U: 8;
    PFNCT_RCS pf_FuncPtr;
    PFNCT_RCS pf_PostFuncPtr;
} RCS_CmdNode;


#define RCS_SOP                         '{'     // 0x7B: Start of Packet
#define RCS_EOP                         '}'     // 0x7D: End of Packet


extern const RCS_Pattern RCS_VerTable[];
extern const INT8U RCS_VerTableTotal;



#endif /* #ifndef __RCS_H__ */

/* EOF */

