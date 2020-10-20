
/*******************************************************************************

   (C) Copyright 2009 RAE Systems Inc.   All rights reserved

----------------- File Information ---------------------------------------------
       File Name: RCS.c
     Description: Common definitions for RCS.

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


/* If implemented in small memory MCU, may reduce some of the items */
const RCS_Pattern RCS_VerTable[] = {
    //Ver, Valid, ChkPattern   SOP Ver Len Dest Src Cmd CmdRev [Data] Chk EOP
    // Data: 0x00-must varify later, 255-refer to LenLen value
    //////////////////////////////////////////////////////////////////////////////////////////
    //Special Packets
    /*
    { 0x00, true,  _CHECKSUM8, 1, 1, 0, 0, 0, 0, 0,    0, 0, 0 }, //0x00  //"Status Query" 7B 00 �� //Satellite Communication use this command
    { 0x01, true,  _CHECKSUM8, 1, 1, 0, 0, 0, 0, 0,    0, 0, 0 }, //0x01  //"Repeat Last" 7B 01 ��
    //0x02-0x09 //for Satellite Communication
    { 0x02, true,  _CHECKSUM8, 1, 1, 0, 0, 0,12, 0,   12, 0, 0 }, //0x02  //Status Packet (for Satellite Communication)
    { 0x03, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x03
    { 0x04, true,  _CHECKSUM8, 1, 1, 0, 0, 0, 0, 0,    0, 0, 0 }, //0x04  //"Unit Info Query"
    { 0x05, true,  _CHECKSUM8, 1, 1, 0, 0, 0,11, 0,   11, 0, 0 }, //0x05  //Unit Info Packet (n = 11)
    { 0x06, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x06
    { 0x07, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x07
    { 0x08, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x08
    { 0x09, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x09

    { 0x0A, true,  _CHECKSUM8, 1, 1, 1, 2, 2, 0, 0,    0, 1, 1 }, //0x0A  //"Polling" 7B 0A ��
    { 0x0B, true,  _CHECKSUM8, 1, 1, 1, 2, 2, 0, 0,  255, 1, 1 }, //0x0B  //"Unit Status" 7B 0B ��
    //0x0C-0x0F
    { 0x0C, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x0C
    { 0x0D, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x0D
    { 0x0E, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x0E
    { 0x0F, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x0F
    */
    //////////////////////////////////////////////////////////////////////////////////////////
    //PSP
    /*
    { 0x10, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x10
    { 0x11, true,  _CHECKSUM8, 1, 1, 0, 0, 0, 0, 0,  255, 0, 1 }, //0x11  //Defined but not used in ProRAE Studio (Not in RCS, suggest to cancel it)
    { 0x12, true,  _CHECKSUM8, 1, 1, 2, 1, 1, 2, 0,  255, 1, 1 }, //0x12  //1.  Defined but not used in ProRAE Studio 2. CMD1 Auto + 1 in Answering Packet
    */
    { 0x13, true,  _CHECKSUM8, 1, 1, 1, 0, 1, 1, 2, 0,  255, 1, 1 }, //0x13  //CMD1 Auto + 1 in Answering Packet

    //0x14-0x1F
    /*
    { 0x14, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x14
    { 0x15, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x15
    { 0x16, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x16
    { 0x17, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x17
    { 0x18, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x18
    { 0x19, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x19
    { 0x1A, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x1A
    { 0x1B, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x1B
    { 0x1C, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x1C
    { 0x1D, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x1D
    { 0x1E, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x1E
    { 0x1F, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x1F
    */
    //////////////////////////////////////////////////////////////////////////////////////////
    //RCS
    /*
    { 0x20, true,  _CHECKSUM8, 1, 1, 1, 1, 1, 1, 0,  255, 1, 1 }, //0x20
    { 0x21, true,  _CHECKSUM8, 1, 1, 1, 1, 1, 1, 0,  255, 1, 0 }, //0x21
    { 0x22, true,  _CHECKSUM8, 1, 1, 1, 1, 1, 1, 0,  255, 0, 1 }, //0x22
    { 0x23, true,  _CHECKSUM8, 1, 1, 1, 1, 1, 1, 0,  255, 0, 0 }, //0x23
    { 0x24, true,  _CHECKSUM8, 1, 1, 1, 1, 1, 2, 0,  255, 1, 1 }, //0x24  //GCRAE, RAEGuards
    { 0x25, true,  _CHECKSUM8, 1, 1, 1, 1, 1, 2, 0,  255, 1, 0 }, //0x25
    { 0x26, true,  _CHECKSUM8, 1, 1, 1, 1, 1, 2, 0,  255, 0, 1 }, //0x26
    { 0x27, true,  _CHECKSUM8, 1, 1, 1, 1, 1, 2, 0,  255, 0, 0 }, //0x27
    { 0x28, true,  _CHECKSUM8, 1, 1, 1, 1, 2, 1, 0,  255, 1, 1 }, //0x28
    { 0x29, true,  _CHECKSUM8, 1, 1, 1, 1, 2, 1, 0,  255, 1, 0 }, //0x29
    { 0x2A, true,  _CHECKSUM8, 1, 1, 1, 1, 2, 1, 0,  255, 0, 1 }, //0x2A
    { 0x2B, true,  _CHECKSUM8, 1, 1, 1, 1, 2, 1, 0,  255, 0, 0 }, //0x2B
    { 0x2C, true,  _CHECKSUM8, 1, 1, 1, 1, 2, 2, 0,  255, 1, 1 }, //0x2C
    { 0x2D, true,  _CHECKSUM8, 1, 1, 1, 1, 2, 2, 0,  255, 1, 0 }, //0x2D
    { 0x2E, true,  _CHECKSUM8, 1, 1, 1, 1, 2, 2, 0,  255, 0, 1 }, //0x2E
    { 0x2F, true,  _CHECKSUM8, 1, 1, 1, 1, 2, 2, 0,  255, 0, 0 }, //0x2F
    { 0x30, true,  _CHECKSUM8, 1, 1, 1, 2, 1, 1, 0,  255, 1, 1 }, //0x30
    { 0x31, true,  _CHECKSUM8, 1, 1, 1, 2, 1, 1, 0,  255, 1, 0 }, //0x31
    { 0x32, true,  _CHECKSUM8, 1, 1, 1, 2, 1, 1, 0,  255, 0, 1 }, //0x32
    { 0x33, true,  _CHECKSUM8, 1, 1, 1, 2, 1, 1, 0,  255, 0, 0 }, //0x33
    { 0x34, true,  _CHECKSUM8, 1, 1, 1, 2, 1, 2, 0,  255, 1, 1 }, //0x34
    { 0x35, true,  _CHECKSUM8, 1, 1, 1, 2, 1, 2, 0,  255, 1, 0 }, //0x35
    { 0x36, true,  _CHECKSUM8, 1, 1, 1, 2, 1, 2, 0,  255, 0, 1 }, //0x36
    { 0x37, true,  _CHECKSUM8, 1, 1, 1, 2, 1, 2, 0,  255, 0, 0 }, //0x37
    */
    { 0x38, true,  _CHECKSUM8, 1, 1, 1, 0, 2, 2, 1, 0,  255, 1, 1 }, //0x38  //RAEWatch
    /*
    { 0x39, true,  _CHECKSUM8, 1, 1, 1, 2, 2, 1, 0,  255, 1, 0 }, //0x39
    { 0x3A, true,  _CHECKSUM8, 1, 1, 1, 2, 2, 1, 0,  255, 0, 1 }, //0x3A
    { 0x3B, true,  _CHECKSUM8, 1, 1, 1, 2, 2, 1, 0,  255, 0, 0 }, //0x3B
    { 0x3C, true,  _CHECKSUM8, 1, 1, 1, 2, 2, 2, 0,  255, 1, 1 }, //0x3C
    { 0x3D, true,  _CHECKSUM8, 1, 1, 1, 2, 2, 2, 0,  255, 1, 0 }, //0x3D
    { 0x3E, true,  _CHECKSUM8, 1, 1, 1, 2, 2, 2, 0,  255, 0, 1 }, //0x3E
    { 0x3F, true,  _CHECKSUM8, 1, 1, 1, 2, 2, 2, 0,  255, 0, 0 }, //0x3F
    { 0x40, true,  _CHECKSUM8, 1, 1, 2, 1, 1, 1, 0,  255, 1, 1 }, //0x40
    */
    { 0x41, true,  _CRC16,     1, 1, 2, 0, 0, 0, 2, 1,  140, 2, 1 }, //0x41
    /*
    { 0x42, true,  _CRC16,     1, 1, 2, 2, 2, 2, 1,  255, 2, 1 }, //0x42

    { 0x43, true,  _CHECKSUM8, 1, 1, 2, 1, 1, 1, 0,  255, 0, 0 }, //0x43
    { 0x44, true,  _CHECKSUM8, 1, 1, 2, 1, 1, 2, 0,  255, 1, 1 }, //0x44
    { 0x45, true,  _CHECKSUM8, 1, 1, 2, 1, 1, 2, 0,  255, 1, 0 }, //0x45
    { 0x46, true,  _CHECKSUM8, 1, 1, 2, 1, 1, 2, 0,  255, 0, 1 }, //0x46
    { 0x47, true,  _CHECKSUM8, 1, 1, 2, 1, 1, 2, 0,  255, 0, 0 }, //0x47
    { 0x48, true,  _CHECKSUM8, 1, 1, 2, 1, 2, 1, 0,  255, 1, 1 }, //0x48
    { 0x49, true,  _CHECKSUM8, 1, 1, 2, 1, 2, 1, 0,  255, 1, 0 }, //0x49
    { 0x4A, true,  _CHECKSUM8, 1, 1, 2, 1, 2, 1, 0,  255, 0, 1 }, //0x4A
    { 0x4B, true,  _CHECKSUM8, 1, 1, 2, 1, 2, 1, 0,  255, 0, 0 }, //0x4B
    { 0x4C, true,  _CHECKSUM8, 1, 1, 2, 1, 2, 2, 0,  255, 1, 1 }, //0x4C
    { 0x4D, true,  _CHECKSUM8, 1, 1, 2, 1, 2, 2, 0,  255, 1, 0 }, //0x4D
    { 0x4E, true,  _CHECKSUM8, 1, 1, 2, 1, 2, 2, 0,  255, 0, 1 }, //0x4E
    { 0x4F, true,  _CHECKSUM8, 1, 1, 2, 1, 2, 2, 0,  255, 0, 0 }, //0x4F
    { 0x50, true,  _CHECKSUM8, 1, 1, 2, 2, 1, 1, 0,  255, 1, 1 }, //0x50

    { 0x51, true,  _CHECKSUM8, 1, 1, 2, 2, 1, 1, 1,  255, 1, 0 }, //0x51
    { 0x52, true,  _CHECKSUM8, 1, 1, 2, 2, 1, 1, 1,  255, 0, 1 }, //0x52
    { 0x53, true,  _CHECKSUM8, 1, 1, 2, 2, 1, 1, 1,  255, 0, 0 }, //0x53
    { 0x54, true,  _CHECKSUM8, 1, 1, 2, 2, 1, 2, 1,  255, 1, 1 }, //0x54

    { 0x55, true,  _CHECKSUM8, 1, 1, 2, 2, 1, 2, 0,  255, 1, 0 }, //0x55
    { 0x56, true,  _CHECKSUM8, 1, 1, 2, 2, 1, 2, 0,  255, 0, 1 }, //0x56
    { 0x57, true,  _CHECKSUM8, 1, 1, 2, 2, 1, 2, 0,  255, 0, 0 }, //0x57
    { 0x58, true,  _CHECKSUM8, 1, 1, 2, 2, 2, 1, 0,  255, 1, 1 }, //0x58
    */
   
    { 0x59, true,  _CRC16,     1, 1, 1, 2, 0, 0, 1, 0,  255, 2, 1 }, //0x59
    
    /*
    { 0x5A, true,  _CHECKSUM8, 1, 1, 2, 2, 2, 1, 0,  255, 0, 1 }, //0x5A
    { 0x5B, true,  _CHECKSUM8, 1, 1, 2, 2, 2, 1, 0,  255, 0, 0 }, //0x5B  //Reserved for Mesh Radio
    { 0x5C, true,  _CHECKSUM8, 1, 1, 2, 2, 2, 2, 0,  255, 1, 1 }, //0x5C
    { 0x5D, true,  _CHECKSUM8, 1, 1, 2, 2, 2, 2, 0,  255, 1, 0 }, //0x5D  //Reserved for Mesh Radio
    { 0x5E, true,  _CHECKSUM8, 1, 1, 2, 2, 2, 2, 0,  255, 0, 1 }, //0x5E
    { 0x5F, true,  _CHECKSUM8, 1, 1, 2, 2, 2, 2, 0,  255, 0, 0 }, //0x5F
    */
    //////////////////////////////////////////////////////////////////////////////////////////
    //Extension
    { 0x60, true,  _CHECKSUM8, 1, 1, 1, 0, 0, 0, 1, 0,  255, 1, 0 }, //0x60  //3G-PID sensor
// { 0x61, true,  _CHECKSUM8, 1, 1, 1, 0, 0, 2, 0,  255, 0, 1 }, //0x61  iSensor
    { 0x62, true,  _CHECKSUM8, 1, 1, 1, 0, 0, 0, 2, 0,  255, 1, 1 }, //0x62  for AutoRAE2

    //0x63-0x7A
    /*
    { 0x63, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x63
    { 0x64, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x64
    { 0x65, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x65
    { 0x66, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x66
    { 0x67, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x67
    { 0x68, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x68
    { 0x69, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x69
    { 0x6A, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x6A
    { 0x6B, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x6B
    { 0x6C, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x6C
    { 0x6D, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x6D
    { 0x6E, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x6E
    { 0x6F, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x6F
    { 0x70, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x70
    { 0x71, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x71
    { 0x72, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x72
    { 0x73, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x73
    { 0x74, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x74
    { 0x75, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x75
    { 0x76, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x76
    { 0x77, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x77
    { 0x78, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x78
    { 0x79, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x79
    { 0x7A, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x7A
    { 0x7B, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x7B  //Reserved //SOP
    { 0x7C, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x7C
    { 0x7D, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0, 0x00, 0, 0 }, //0x7D  //Reserved //EOP
    //0x7E-0x7F
    { 0x7E, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0,  255, 0, 0 }, //0x7E
    { 0x7F, false, _CHECKSUM8, 1, 0, 0, 0, 0, 0, 0,  255, 0, 0 }, //0x7F
    */
    //0x80-0xBF, Init Packet, no address
    { 0x80, true,  _CHECKSUM8, 1, 1, 0, 0, 0, 0, 0, 0,    0, 0, 1 },
    { 0x88, true,  _CHECKSUM8, 1, 1, 0, 0, 0, 0, 0, 0,    0, 0, 1 },
    { 0x90, true,  _CHECKSUM8, 1, 1, 0, 0, 0, 0, 0, 0,    0, 0, 1 },
    { 0x98, true,  _CHECKSUM8, 1, 1, 0, 0, 0, 0, 0, 0,    2, 0, 1 },
    { 0xA0, true,  _CHECKSUM8, 1, 1, 0, 0, 0, 0, 0,    5, 0, 1 },
    { 0xA8, true,  _CHECKSUM8, 1, 1, 0, 0, 0, 0, 0, 0,    0, 0, 1 },
    { 0xB0, true,  _CHECKSUM8, 1, 1, 0, 0, 0, 0, 0, 0,    0, 0, 1 },
    { 0xB8, true,  _CHECKSUM8, 1, 1, 0, 0, 0, 0, 0, 0,    2, 0, 1 },
    //0xC0-0xFF, Init Packet, with address
    { 0xC0, true,  _CHECKSUM8, 1, 1, 0, 0, 2, 2, 0, 0,    0, 0, 1 },
    { 0xC8, true,  _CHECKSUM8, 1, 1, 0, 0, 2, 2, 0, 0,    0, 0, 1 },
    { 0xD0, true,  _CHECKSUM8, 1, 1, 0, 0, 2, 2, 0, 0,    0, 0, 1 },
    { 0xD8, true,  _CHECKSUM8, 1, 1, 0, 0, 2, 2, 0, 0,    2, 0, 1 },
    { 0xE0, true,  _CHECKSUM8, 1, 1, 0, 0, 2, 2, 0, 0,    5, 0, 1 },
    { 0xE8, true,  _CHECKSUM8, 1, 1, 0, 0, 2, 2, 0, 0,    0, 0, 1 },
    { 0xF0, true,  _CHECKSUM8, 1, 1, 0, 0, 2, 2, 0, 0,    0, 0, 1 },
    { 0xF8, true,  _CHECKSUM8, 1, 1, 0, 0, 2, 2, 0, 0,    2, 0, 1 },
};

const INT8U RCS_VerTableTotal = dim(RCS_VerTable);



/* EOF */

