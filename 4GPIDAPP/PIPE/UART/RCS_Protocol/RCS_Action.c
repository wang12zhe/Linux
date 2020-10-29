
/*******************************************************************************

   (C) Copyright 2009 RAE Systems Inc.   All rights reserved

----------------- File Information ---------------------------------------------
       File Name: RCS_Action.c
     Description: RCS Protocol Action.

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
Last Modify Date: 3/17/2009
     Description: Revised totally, try to support all version code.

*******************************************************************************/


//#include "Includes.h"
#include "includes.h"


void Cmd_Received(RCS_t *rcs)
{
    PFNCT_RCS post_fptr = NULL;

    if (RCS_Builder(rcs, &post_fptr) == 0) {
        return;
    }

    // Send out response package
    RCS_SendPackage(rcs);

    // Post execution
    if (post_fptr != NULL) {
        post_fptr(rcs);
    }
}


void Init_Received(RCS_t *rcs)
{
    INT8U ret = 0;
    INT8U u8_tmp;
    INT8U initCode;
    INT8U initPara;

    u8_tmp = rcs->InitPac & 0xF8;
    rcs->RespLen = 0;
    rcs->RespBuf[rcs->RespLen++] = RCS_SOP;
    initCode = (rcs->InitPac >> 3) & 0x07;
    initPara = rcs->InitPac & 0x07;
    switch (initCode) {
        case 0:
            rcs->RespBuf[rcs->RespLen++] = u8_tmp | 0x06;   // RCS,P2P
            if (rcs->InitPac & 0x40) {
                rcs->RespBuf[rcs->RespLen++] = rcs->HostAddr >> 8;
                rcs->RespBuf[rcs->RespLen++] = rcs->HostAddr;
                rcs->RespBuf[rcs->RespLen++] = rcs->SlaveAddr >> 8;
                rcs->RespBuf[rcs->RespLen++] = rcs->SlaveAddr;
            }
            ret = 1;
            break;
        case 1:
            /*
                        if (initPara == 0x01) {
                            // request use AutoRAE
                            rcs->RespBuf[rcs->RespLen++] = u8_tmp | initPara;
                        }
                        else
            */
            if (initPara == 0x02) {
                // request use P2P
                rcs->RespBuf[rcs->RespLen++] = u8_tmp | initPara;
            }
            else if (initPara == 0x04) {
                // request use RCS
                rcs->RespBuf[rcs->RespLen++] = u8_tmp | initPara;
            }
            else {
                // wrong parameter
                rcs->RespBuf[rcs->RespLen++] = u8_tmp;
            }
            if (rcs->InitPac & 0x40) {
                rcs->RespBuf[rcs->RespLen++] = rcs->HostAddr >> 8;
                rcs->RespBuf[rcs->RespLen++] = rcs->HostAddr;
                rcs->RespBuf[rcs->RespLen++] = rcs->SlaveAddr >> 8;
                rcs->RespBuf[rcs->RespLen++] = rcs->SlaveAddr;
            }
            ret = 1;
            break;
        case 2:
        /*
            rcs->RespBuf[rcs->RespLen++] = rcs->InitPac;
            if (rcs->InitPac & 0x40) {
                rcs->RespBuf[rcs->RespLen++] = rcs->HostAddr >> 8;
                rcs->RespBuf[rcs->RespLen++] = rcs->HostAddr;
                rcs->RespBuf[rcs->RespLen++] = rcs->SlaveAddr >> 8;
                rcs->RespBuf[rcs->RespLen++] = rcs->SlaveAddr;
            }
            rcs->RespBuf[rcs->RespLen++] = PCF1;
            rcs->RespBuf[rcs->RespLen++] = PCF2;
            rcs->RespBuf[rcs->RespLen++] = DevInfo1;
            rcs->RespBuf[rcs->RespLen++] = DevInfo2;
            rcs->RespBuf[rcs->RespLen++] = DevInfo3;
            rcs->RespBuf[rcs->RespLen++] = DevInfo4;
            rcs->RespBuf[rcs->RespLen++] = DevInfo5;
            rcs->RespBuf[rcs->RespLen++] = DevInfo6;
        */
        case 3:
        case 4:
        case 5:
            break;
        case 6:
            rcs->RespBuf[rcs->RespLen++] = rcs->InitPac;
            if (rcs->InitPac & 0x40) {
                rcs->RespBuf[rcs->RespLen++] = rcs->HostAddr >> 8;
                rcs->RespBuf[rcs->RespLen++] = rcs->HostAddr;
                rcs->RespBuf[rcs->RespLen++] = rcs->SlaveAddr >> 8;
                rcs->RespBuf[rcs->RespLen++] = rcs->SlaveAddr;
            }
            rcs->RespBuf[rcs->RespLen++] = 0x13;
            rcs->RespBuf[rcs->RespLen++] = 0x38;
            rcs->RespBuf[rcs->RespLen++] = 0x00;
            rcs->RespBuf[rcs->RespLen++] = 0x00;
            rcs->RespBuf[rcs->RespLen++] = 0x00;
            rcs->RespBuf[rcs->RespLen++] = 0x00;
            rcs->RespBuf[rcs->RespLen++] = 0x00;
            rcs->RespBuf[rcs->RespLen++] = 0x00;
            rcs->RespBuf[rcs->RespLen++] = 0x00;
            ret = 1;
            break;
        case 7:
            // request use specific version
            if (rcs->DataBuf[0] == rcs->DataBuf[1]) {
                rcs->RespBuf[rcs->RespLen++] = rcs->InitPac | 0x40;
                rcs->RespBuf[rcs->RespLen++] = rcs->HostAddr >> 8;
                rcs->RespBuf[rcs->RespLen++] = rcs->HostAddr;
                rcs->RespBuf[rcs->RespLen++] = rcs->SlaveAddr >> 8;
                rcs->RespBuf[rcs->RespLen++] = rcs->SlaveAddr;
                rcs->RespBuf[rcs->RespLen++] = rcs->DataBuf[0];
                rcs->RespBuf[rcs->RespLen++] = rcs->DataBuf[0];
                ret = 1;
            }
            break;
    }
    rcs->RespBuf[rcs->RespLen++] = RCS_EOP;
    if (ret) {
        // Send out response package
        RCS_SendPackage(rcs);
    }
    // if need to do further post-process, add...

}


void InitResp_Recieved(RCS_t *rcs)
{
}

void CmdResp_Received(RCS_t *rcs)
{
    RCS_Executer(rcs);
}


void RCS_Action(RCS_t *rcs)
{
    switch (rcs->Role) {
        case SLAVE_SEND:
            if (rcs->PacketFlags_bit.PF_INIT == 1) {
                Init_Received(rcs);
            }
            else {
                Cmd_Received(rcs);
            }
            break;
        case HOST_RECV:
            if (rcs->PacketFlags_bit.PF_INIT == 1) {
                InitResp_Recieved(rcs);
            }
            else {
                CmdResp_Received(rcs);
            }
            break;
        default:
            break;
    }
    rcs->PacketFlags_bit.PF_ACTION = 0;
}


/* EOF */

