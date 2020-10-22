
/*******************************************************************************

   (C) Copyright 2009 RAE Systems Inc.   All rights reserved

----------------- File Information ---------------------------------------------
       File Name: RCS_Builder.c
     Description: RCS Protocol Builder.

---------------- Important Notes -----------------------------------------------


----------------- Rivision History ---------------------------------------------
         Version: V1.00
          Author: Alven Lu
Last Modify Date: 3/23/2009
     Description: Initial version

*******************************************************************************/


#include "includes.h"

typedef void (*PFNCT_PUTC)(int fd,INT8U *, INT8U);

/* return 1: success, 0: not support */
INT8U RCS_SendPackage(RCS_t *rcs)
{
    PFNCT_PUTC fp_UartPut = NULL;
    INT16U i;

    if (rcs->PacketFlags_bit.PF_NORESP) {
        rcs->PacketFlags_bit.PF_NORESP = 0;
        return 1;
    }

    if (rcs->pf_FuncPut != NULL) {
        fp_UartPut = (PFNCT_PUTC)rcs->pf_FuncPut;
        if (rcs->PacketFlags_bit.PF_REPEAT == 1) {
            for (i = 0; i < rcs->RespLen; i++) {
                if (i != 0 && i != (rcs->RespLen - 1)) {
                    if (rcs->RespBuf[i] == RCS_SOP || rcs->RespBuf[i] == RCS_EOP) {
                        fp_UartPut(rcs->fd,rcs->RespBuf + i, 1);
                    }
                }
                fp_UartPut(rcs->fd,rcs->RespBuf + i, 1);
            }
        }
        else {
           fp_UartPut(rcs->fd,rcs->RespBuf, rcs->RespLen); 
        }
        return 1;
    }
    return 0;
}

void RCS_CmdRevChk(RCS_t *rcs, INT8U rev)
{
    if (rcs->PktCfg->CmdRevLen) {
        rcs->CmdVer = rev;
    }
}

/* return 1: support, 0: not support */
INT8U RCS_SearchCmd(RCS_t *rcs, PFNCT_RCS *func, PFNCT_RCS *post_func)
{
    RCS_CmdNode *tptr;
    INT16U i;

    /* Search command set */
    tptr = (RCS_CmdNode *)rcs->CmdTable;
    for (i = 0; i < rcs->CmdTotal; i++) {
        if (rcs->Cmd == (tptr + i)->u16_Code) {
            RCS_CmdRevChk(rcs, ((tptr + i)->u8_CmdRev));
            *func = (PFNCT_RCS)(tptr + i)->pf_FuncPtr;
            *post_func = (PFNCT_RCS)(tptr + i)->pf_PostFuncPtr;
            return 1;
        }
    }
    return 0;
}


/* return 1: support, 0: not support
 *
 * HOST_RECV only
 *
 */
INT8U RCS_Executer(RCS_t *rcs)
{
    PFNCT_RCS fptr = NULL;
    PFNCT_RCS post_fptr = NULL;

    if (rcs->Role != HOST_RECV) {
        goto exit;
    }

    if (RCS_SearchCmd(rcs, &fptr, &post_fptr) == 0) {
        goto exit;
    }

    if (fptr != NULL) {
        fptr(rcs);
    }
    if (post_fptr != NULL) {
        post_fptr(rcs);
    }
    return 1;

exit:
    return 0;
}


/* return 1: support, 0: not support
 *
 * HOST_SEND and SLAVE_SEND only
 *
 */
INT8U RCS_Builder(RCS_t *rcs, PFNCT_RCS *post_func)
{
    PFNCT_RCS fptr = NULL;
    PFNCT_RCS post_fptr = NULL;

    INT16U i;
    INT16U index_len;

    if (rcs->Role == HOST_RECV) {
        goto exit;
    }

    if (RCS_PatternCheck(rcs) == 0) {
        goto exit;
    }

    if (RCS_SearchCmd(rcs, &fptr, &post_fptr) == 0) {
        rcs->CommStatus_bit.CS_ERR_CMD = 1;
    }

    i = 0;
    rcs->RespBuf[i++] = RCS_SOP;
    rcs->RespBuf[i++] = rcs->VerPac;

    // not the final output len, just an index of RespBuf.
    rcs->RespLen = rcs->PktCfg->SOPLen + rcs->PktCfg->VerLen
                   + rcs->PktCfg->LenLen + rcs->PktCfg->IndexLen
                   + rcs->PktCfg->DestLen + rcs->PktCfg->SrcLen 
                   + rcs->PktCfg->CmdLen + rcs->PktCfg->CmdRevLen;

    index_len = i;
    switch (rcs->PktCfg->LenLen) {
        case 2:
            rcs->RespBuf[i++] = 0;      // Dummy len here, corrected later
        case 1:
            rcs->RespBuf[i++] = 0;      // Dummy len here, corrected later
            break;
        default:
            break;
    }
    switch (rcs->PktCfg->IndexLen) {
        case 2:
            rcs->RespBuf[i++] = rcs-> PktIndex  >> 8;      
        case 1:
            rcs->RespBuf[i++] = rcs-> PktIndex;    
            break;
        default:
            break;
    }

    switch (rcs->PktCfg->DestLen) {
        case 2:
            if (rcs->Role == HOST_SEND) {
                rcs->RespBuf[i++] = rcs->SlaveAddr >> 8;
            }
            else {
                rcs->RespBuf[i++] = rcs->HostAddr >> 8;
            }
        case 1:
            if (rcs->Role == HOST_SEND) {
                rcs->RespBuf[i++] = rcs->SlaveAddr;
            }
            else {
                rcs->RespBuf[i++] = rcs->HostAddr;
            }
            break;
        default:
            break;
    }

    switch (rcs->PktCfg->SrcLen) {
        case 2:
            if (rcs->Role == HOST_SEND) {
                rcs->RespBuf[i++] = rcs->HostAddr >> 8;
            }
            else {
                rcs->RespBuf[i++] = rcs->SlaveAddr >> 8;
            }
        case 1:
            if (rcs->Role == HOST_SEND) {
                rcs->RespBuf[i++] = rcs->HostAddr;
            }
            else {
                rcs->RespBuf[i++] = rcs->SlaveAddr;
            }
            break;
        default:
            break;
    }

    if (rcs->CommStatus_bit.CS_ERR_CMD == 1) {
        if (rcs->Role == HOST_SEND) {
            goto exit;
        }
        else {
            switch (rcs->PktCfg->CmdLen) {
                case 2:
                    rcs->RespBuf[i++] = RCS_ERROR_SLAVE >> 8;
                    rcs->RespBuf[i++] = rcs->Cmd;
                    break;
                case 1:
                    rcs->RespBuf[i++] = RCS_ERROR_SLAVE >> 8;
                    break;
                default:
                    break;
            }
            rcs->RtnCode = FAIL_INVALIDCMD;
            rcs->RespBuf[i++] = rcs->RtnCode;
            rcs->RespLen++;
        }
    }
    else {
        if (fptr != NULL) {
            fptr(rcs);
        }
        if (rcs->CommStatus_bit.CS_ERR_DATA == 1) {
            switch (rcs->PktCfg->CmdLen) {
                case 2:
                    rcs->RespBuf[i++] = RCS_ERROR_SLAVE >> 8;
                    rcs->RespBuf[i++] = rcs->Cmd;
                    break;
                case 1:
                    rcs->RespBuf[i++] = RCS_ERROR_SLAVE >> 8;
                    break;
                default:
                    break;
            }
            rcs->RespBuf[i++] = rcs->RtnCode;
            rcs->RespLen++;
        }
        else if (rcs->CommStatus_bit.CS_ERR_BUSY == 1) {
            switch (rcs->PktCfg->CmdLen) {
                case 2:
                    rcs->RespBuf[i++] = (rcs->Cmd >> 8) | 0x80;
                    rcs->RespBuf[i++] = rcs->Cmd;
                    break;
                case 1:
                    rcs->RespBuf[i++] = rcs->Cmd | 0x80;
                    break;
                default:
                    break;
            }
        }
        else {
            switch (rcs->PktCfg->CmdLen) {
                case 2:
                    if (rcs->Role == HOST_SEND) {
                        rcs->RespBuf[i++] = rcs->Cmd >> 8;
                    }
                    else {
                        rcs->RespBuf[i++] = (rcs->Cmd >> 8) + 1;
                    }
                    rcs->RespBuf[i++] = rcs->Cmd;
                    break;
                case 1:
                    if (rcs->Role == HOST_SEND) {
                        rcs->RespBuf[i++] = rcs->Cmd;
                    }
                    else {
                        if (rcs->VerPac == 0x38) {
                            // WSN special process
                            rcs->RespBuf[i++] = rcs->Cmd;
                        }
                        else {
                            rcs->RespBuf[i++] = rcs->Cmd + 1;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    switch (rcs->PktCfg->CmdRevLen) {
        case 1:
            rcs->RespBuf[i++] = rcs->CmdVer;
            break;
        default:
            break;
    }

    i = rcs->RespLen;
    rcs->RespLen = i + rcs->PktCfg->ChkLen + rcs->PktCfg->EOPLen
                   - rcs->PktCfg->SOPLen - rcs->PktCfg->VerLen
                   - rcs->PktCfg->LenLen;
    switch (rcs->PktCfg->LenLen) {
        case 2:
            rcs->RespBuf[index_len++] = rcs->RespLen >> 8;
        case 1:
            rcs->RespBuf[index_len++] = rcs->RespLen;
            break;
        default:
            break;
    }

    rcs->RespLen = i;
    switch (rcs->PktCfg->ChkLen) {
        case 1:
            if (rcs->PktCfg->ChkPattern == _CHECKSUM8) {
                rcs->RespBuf[i++] = UTL_CalChkSum8to8(rcs->RespBuf, rcs->RespLen);
            }
            break;
        case 2:
            if (rcs->PktCfg->ChkPattern == _CRC16) {
                INT16U temp = CRC16_All(rcs->RespBuf, rcs->RespLen);
                rcs->RespBuf[i++] = (INT8U)(temp >> 8);
                rcs->RespBuf[i++] = (INT8U)(temp);
            }
            break;
        default:
            break;
    }

    switch (rcs->PktCfg->EOPLen) {
        case 1:
            rcs->RespBuf[i++] = RCS_EOP;
            break;
        default:
            break;
    }

    rcs->RespLen = i;
    if (post_fptr != NULL) {
        *post_func = post_fptr;
    }
    return 1;

exit:
    return 0;
}



/* EOF */


