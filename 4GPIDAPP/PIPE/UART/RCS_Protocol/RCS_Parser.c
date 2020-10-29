
/*******************************************************************************

   (C) Copyright 2009 RAE Systems Inc.   All rights reserved

----------------- File Information ---------------------------------------------
       File Name: RCS_Parser.c
     Description: RCS Protocol Parser.

---------------- Important Notes -----------------------------------------------
    If used for small RAM/ROM system, reduce the RCS_VerTable as needed.

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

#include "includes.h"

/* return 1: supported, 0: not support */
INT8U RCS_PatternCheck(RCS_t *rcs)
{
    INT8U i;
    INT8U ver = rcs->VerPac;

    if (ver < 0x80) {
        /*
                if (ver != rcs->VerPac) {
                    return 0;
                }
        */
    }
    else {
        ver &= 0xF8;        // Lower 3 bits are parameters
    }

    for (i = 0; i < RCS_VerTableTotal; i++) {
        if (ver == RCS_VerTable[i].Ver) {
            if (RCS_VerTable[i].Valid == false) {
                return 0;
            }
            rcs->PktCfg = (RCS_Pattern *)&RCS_VerTable[i];
            if (ver <= 0x0F) {
                rcs->InitPac = rcs->VerPac;
                rcs->PacketFlags_bit.PF_SPECIAL = 1;
            }
            else if ((ver >= 0x10) && (ver <= 0x1F)) {
                rcs->PacketFlags_bit.PF_REPEAT = 1;
            }
            else if (ver >= 0x80) {
                rcs->InitPac = rcs->VerPac;
                rcs->PacketFlags_bit.PF_INIT = 1;
            }
            rcs->VerPac = ver;
            return 1;
        }
    }
    return 0;
}


void GetNextCheckField(RCS_t *rcs)
{
    RCS_STATE curStep = rcs->StateStep;

    while (1) {
        switch (curStep) {
            case _RCS_SOP:
                rcs->StateStep = _RCS_VER;
                return;
            case _RCS_VER:
                if (rcs->PktCfg->LenLen == 0) {
                    rcs->DataLen = rcs->PktCfg->DataLen;
                    curStep = _RCS_LEN_LSB;
                    break;
                }
                else if (rcs->PktCfg->LenLen == 2) {
                    rcs->StateStep = _RCS_LEN_MSB;
                    return;
                }
                else {
                    rcs->StateStep = _RCS_LEN_LSB;
                    return;
                }
            case _RCS_LEN_MSB:
                rcs->StateStep = _RCS_LEN_LSB;
                return;
            case _RCS_LEN_LSB:
                 if (rcs->PktCfg->IndexLen == 0) {
                    curStep = _RCS_INDEX_LSB;
                    break;
                }
                else if (rcs->PktCfg->IndexLen == 2) {
                    rcs->StateStep = _RCS_INDEX_MSB;
                    return;
                }
                else {
                    rcs->StateStep = _RCS_INDEX_LSB;
                    return;
                }
                break;         
            case _RCS_INDEX_MSB:
                rcs->StateStep = _RCS_INDEX_LSB;
                return;
            case _RCS_INDEX_LSB:
                if (rcs->PktCfg->DestLen == 0) {
                    curStep = _RCS_DST_LSB;
                    break;
                }
                else if (rcs->PktCfg->DestLen == 2) {
                    rcs->StateStep = _RCS_DST_MSB;
                    return;
                }
                else {
                    rcs->StateStep = _RCS_DST_LSB;
                    return;
                }
            case _RCS_DST_MSB:
                rcs->StateStep = _RCS_DST_LSB;
                return;
            case _RCS_DST_LSB:
                if (rcs->PktCfg->SrcLen == 0) {
                    curStep = _RCS_SRC_LSB;
                    break;
                }
                else if (rcs->PktCfg->SrcLen == 2) {
                    rcs->StateStep = _RCS_SRC_MSB;
                    return;
                }
                else {
                    rcs->StateStep = _RCS_SRC_LSB;
                    return;
                }
            case _RCS_SRC_MSB:
                rcs->StateStep = _RCS_SRC_LSB;
                return;
            case _RCS_SRC_LSB:
                if (rcs->PktCfg->CmdLen == 0) {
                    curStep = _RCS_CMD2;
                    break;
                }
                else if (rcs->PktCfg->CmdLen == 2) {
                    rcs->StateStep = _RCS_CMD1;
                    return;
                }
                else {
                    rcs->StateStep = _RCS_CMD2;
                    return;
                }
            case _RCS_CMD1:
                rcs->StateStep = _RCS_CMD2;
                return;
            case _RCS_CMD2:
                if (rcs->PktCfg->CmdRevLen == 0) {
                    curStep = _RCS_CMDREV;
                    break;
                }
                else {
                    rcs->StateStep = _RCS_CMDREV;
                    return;
                }
            case _RCS_CMDREV:
                if (rcs->DataLen == 0) {
                    curStep = _RCS_DATA;
                    break;
                }
                else {
                    rcs->StateStep = _RCS_DATA;
                    return;
                }
            case _RCS_DATA:
                if (rcs->PktCfg->ChkLen == 0) {
                    curStep = _RCS_EOP;
                    break;
                }
                else {
                    if (rcs->PktCfg->ChkPattern == _CHECKSUM8) {
                        rcs->StateStep = _RCS_CHK;
                        return;
                    }
                    else if (rcs->PktCfg->ChkPattern == _CRC16) {
                        rcs->StateStep = _RCS_CRCH;
                        return;
                    }
                    else {
                        rcs->StateStep = _RCS_SOP;
                        return;
                    }
                }
            case _RCS_CHK:
                if (rcs->PktCfg->EOPLen == 0) {
                    curStep = _RCS_EOP;
                    break;
                }
                else {
                    rcs->StateStep = _RCS_EOP;
                    return;
                }
            case _RCS_CRCH:
                rcs->StateStep = _RCS_CRCL;
                return;
            case _RCS_CRCL:
                if (rcs->PktCfg->EOPLen == 0) {
                    curStep = _RCS_EOP;
                    break;
                }
                else {
                    rcs->StateStep = _RCS_EOP;
                    return;
                }
            case _RCS_EOP:
                rcs->PacketFlags_bit.PF_ACTION = 1;
            default:
                rcs->StateStep = _RCS_SOP;
                return;
        }
    }
}



void RCS_Check_SOP(RCS_t *rcs)
{
    INT8U inByte = rcs->InByte;

    if (inByte == RCS_SOP) {
        rcs->CheckSum = inByte;
        rcs->DataIndex = 0;
        rcs->PktLen = 0;
        rcs->DataLen = 0;
        rcs->Cmd = 0;
        rcs->DestAddr = 0;
        rcs->SrcAddr = 0;
        rcs->PktCfg = NULL;
        rcs->PacketFlags = 0;
        rcs->CommStatus = 0;
        rcs->InitPac = 0;
        GetNextCheckField(rcs);
    }
}

void RCS_Check_VerPac(RCS_t *rcs)
{
    rcs->VerPac = rcs->InByte;
    if (RCS_PatternCheck(rcs) == 0) {
        rcs->StateStep = _RCS_SOP;
        return;
    }
    GetNextCheckField(rcs);
}

void RCS_Check_LenMSB(RCS_t *rcs)
{
    INT8U inByte = rcs->InByte;

    rcs->PktLen = inByte;
    rcs->PktLen <<= 8;
    rcs->PktLen &= 0xFF00;

    GetNextCheckField(rcs);
}


void RCS_Check_LenLSB(RCS_t *rcs)
{
    INT8U inByte = rcs->InByte;
    INT16U minLen;

    minLen = rcs->PktCfg->DestLen + rcs->PktCfg->SrcLen + rcs->PktCfg->IndexLen+ rcs->PktCfg->CmdLen
             + rcs->PktCfg->CmdRevLen + rcs->PktCfg->ChkLen + rcs->PktCfg->EOPLen;
    rcs->PktLen += inByte;
    if ((rcs->PktLen >= minLen) && ((rcs->PktLen - minLen) <= rcs->DataBufLen)) {
        rcs->DataLen = rcs->PktLen - minLen;
    }
    else {
        rcs->StateStep = _RCS_SOP;
        return;
    }

    GetNextCheckField(rcs);
}
void RCS_Check_IndexMSB(RCS_t *rcs)
{
   // 20200416 sensor response index error,so not check index now 
     /*
    INT8U Index = rcs->PktIndex >> 8;

    if (Index == rcs->InByte ) {
        GetNextCheckField(rcs);
    }
    else {
        rcs->StateStep = _RCS_SOP;
        return;
    } 
   */
  
    GetNextCheckField(rcs);
}
void RCS_Check_IndexLSB(RCS_t *rcs)
{
    // 20200416 sensor response index error,so not check index now 
    /*
    INT8U Index = rcs->PktIndex & 0XFF;

    if (Index == rcs->InByte ) {
        GetNextCheckField(rcs);
    }
    else {
        rcs->StateStep = _RCS_SOP;
        return;
    }
  
    */
    GetNextCheckField(rcs);
}

void RCS_Check_DestMSB(RCS_t *rcs)
{
  
    INT8U inByte = rcs->InByte;

    rcs->DestAddr = inByte;
    rcs->DestAddr <<= 8;
    rcs->DestAddr &= 0xFF00;

    GetNextCheckField(rcs);
}


void RCS_Check_DestLSB(RCS_t *rcs)
{
    INT8U inByte = rcs->InByte;

    rcs->DestAddr += inByte;
    if (rcs->PktCfg->DestLen == 2) {
        if (rcs->DestAddr == 0xFFFF) {
            rcs->PacketFlags_bit.PF_BROADCAST = 1;
        }
    }
    else {
        if (rcs->DestAddr == 0xFF) {
            rcs->PacketFlags_bit.PF_BROADCAST = 1;
        }
    }
#if RCS_CHK_DST_SRC_ID
    if ((rcs->PacketFlags_bit.PF_BROADCAST == 0) && (rcs->DestAddr != rcs->SlaveAddr)) {
        rcs->StateStep = _RCS_SOP;
        return;
    }
#endif
    GetNextCheckField(rcs);
}


void RCS_Check_SrcMSB(RCS_t *rcs)
{
    INT8U inByte = rcs->InByte;

    rcs->SrcAddr = inByte;
    rcs->SrcAddr <<= 8;
    rcs->SrcAddr &= 0xFF00;

    GetNextCheckField(rcs);
}


void RCS_Check_SrcLSB(RCS_t *rcs)
{
    INT8U inByte = rcs->InByte;

    rcs->SrcAddr += inByte;
#if RCS_CHK_DST_SRC_ID
    if (rcs->SrcAddr != rcs->HostAddr) {
        rcs->StateStep = _RCS_SOP;
        return;
    }
#endif
    GetNextCheckField(rcs);
}


void RCS_Check_Cmd1(RCS_t *rcs)
{
    INT8U inByte = rcs->InByte;

    rcs->Cmd = inByte;
    rcs->Cmd <<= 8;
    rcs->Cmd &= 0xFF00;

    GetNextCheckField(rcs);
}


void RCS_Check_Cmd2(RCS_t *rcs)
{
    INT8U inByte = rcs->InByte;

    rcs->Cmd += inByte;

    GetNextCheckField(rcs);
}

void RCS_Check_CmdRev(RCS_t *rcs)
{
    rcs->CmdRev = rcs->InByte;
    GetNextCheckField(rcs);
}

void RCS_Check_Data(RCS_t *rcs)
{
    INT8U inByte = rcs->InByte;

    *(rcs->DataBuf + rcs->DataIndex) = inByte;

    rcs->DataIndex++;
    if (rcs->DataIndex < rcs->DataLen) {
        return;
    }
    GetNextCheckField(rcs);
}


void RCS_Check_Checksum(RCS_t *rcs)
{
    if (rcs->CheckSum != 0) {
        rcs->StateStep = _RCS_SOP;
        return;
    }
    GetNextCheckField(rcs);
}

void RCS_Check_CRCH(RCS_t *rcs)
{
    INT8U inByte = rcs->InByte;

    if (inByte != (INT8U)(rcs->CRC16 >> 8)) {
        rcs->StateStep = _RCS_SOP;
        return;
    }
    GetNextCheckField(rcs);
}

void RCS_Check_CRCL(RCS_t *rcs)
{
    INT8U inByte = rcs->InByte;

    if (inByte != (INT8U)(rcs->CRC16)) {
        rcs->StateStep = _RCS_SOP;
        return;
    }
    GetNextCheckField(rcs);
}

void RCS_Check_EOP(RCS_t *rcs)
{
    INT8U inByte = rcs->InByte;

    GetNextCheckField(rcs);
    if (inByte != RCS_EOP) {
        rcs->PacketFlags_bit.PF_ACTION = 0;
    }
}

/* must match with RCS_STATE total number */
void (* const RCS_Check[])(RCS_t *) = {
    RCS_Check_SOP,
    RCS_Check_VerPac,
    RCS_Check_LenMSB,
    RCS_Check_LenLSB,
    RCS_Check_IndexMSB,
    RCS_Check_IndexLSB,
    RCS_Check_DestMSB,
    RCS_Check_DestLSB,
    RCS_Check_SrcMSB,
    RCS_Check_SrcLSB,
    RCS_Check_Cmd1,
    RCS_Check_Cmd2,
    RCS_Check_CmdRev,
    RCS_Check_Data,
    RCS_Check_Checksum,
    RCS_Check_CRCH,
    RCS_Check_CRCL,
    RCS_Check_EOP,
};

void RCS_CalCRC16(RCS_t *rcs)
{
    /*
     if (rcs->PktCfg->ChkPattern != _CRC16) {
         return;
     }
     */

    switch (rcs->StateStep) {
        case _RCS_SOP:
            rcs->CRC16 = CRC16_Single(0x0000, rcs->InByte);
            break;
        case _RCS_CRCL:
            rcs->CRC16 = CRC16_Result(rcs->CRC16);
            break;
        case _RCS_VER:
        case _RCS_LEN_MSB:
        case _RCS_LEN_LSB:
        case _RCS_INDEX_MSB:
        case _RCS_INDEX_LSB:
        case _RCS_DST_MSB:
        case _RCS_DST_LSB:
        case _RCS_SRC_MSB:
        case _RCS_SRC_LSB:
        case _RCS_CMD1:
        case _RCS_CMD2:
        case _RCS_CMDREV:
        case _RCS_DATA:
            rcs->CRC16 = CRC16_Single(rcs->CRC16, rcs->InByte);
            break;
        default:
            break;
    }
}

void RCS_Parser(RCS_t *rcs, INT8U inByte)
{
    if (rcs->StateStep > _RCS_EOP) {
        rcs->StateStep = _RCS_SOP;
    }
    if (rcs->PacketFlags_bit.PF_REPEAT == 1) {
        if (rcs->PacketFlags_bit.PF_REPEATED == 1) {
            rcs->PacketFlags_bit.PF_REPEATED = 0;
            if (inByte != rcs->InByte) {
                rcs->StateStep = _RCS_SOP;
            }
            return; // Drop this repeat byte
        }
        else {
            if ((rcs->StateStep != _RCS_SOP) && (rcs->StateStep != _RCS_EOP) &&
                    ((inByte == RCS_SOP) || (inByte == RCS_EOP))) {
                rcs->PacketFlags_bit.PF_REPEATED = 1;
            }
        }
    }
    rcs->InByte = inByte;
    rcs->CheckSum += inByte;
    RCS_CalCRC16(rcs);
    RCS_Check[rcs->StateStep](rcs);
}

void RCS_ParserReset(RCS_t *rcs)
{
    rcs->StateStep = _RCS_SOP;
}

/* End of File */



