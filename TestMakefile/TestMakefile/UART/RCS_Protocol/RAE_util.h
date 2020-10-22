/*******************************************************************************

     RAE Utility

   (C) Copyright 2006, RAE Systems Inc.      All rights reserved

--------------------------------------------------------------------------------

     File name: RAE_util.H
      Hardware: ARM7
     Reference:

--------------------------------------------------------------------------------

   == Important Note ==

--------------------------------------------------------------------------------

   Revision History

   == V1.00.00 ==
      10/29/06 - Wenpeng,

*******************************************************************************/
#ifndef __RAE_UTIL_H
#define __RAE_UTIL_H

#define dim(x) (sizeof(x) / sizeof(x[0])) /* Returns number of elements         */

//void SoftReset(void);

INT32U UTL_GetAverageRaw(INT16U(*pFunc)(INT8U), INT8U u8_ch);
INT8U UTL_CalChkSum8to8(INT8U *buff, INT32U len);
INT8U UTL_CheckSum8(INT8U *u8p_Ptr, INT32U u32_Len);

INT32U UTL_CheckSum32(INT32U *u32p_Ptr, INT32U u32_Len);
INT32U VerifyCheckSum8to32(INT8U *buff, INT32U len);
INT32U CalCheckSum8to32(INT8U *buff, INT32U len);
INT32U UTL_FindRange(INT32U u32_Num, INT32U *u32p_Table, INT32U u32_Len) ;
INT32U STR_Length(STRING Str);
INT32U UTL_Date2Minute(INT8U *Date);
INT8U UTL_Byte2Deci(INT8U byte, INT8U *buff);
void UTL_Byte2DeciS(INT8U byte, INT8U *buff, INT8U ch);
INT8U UTL_Word2Deci(INT16U word, INT8U *buff);
void UTL_Word2DeciS(INT16U word, INT8U *buff, INT8U ch);
INT32U UTL_Long2Deci(INT32U LongWord, INT8U *buff, INT32U mdigit);
void UTL_Long2DeciS(INT32U LongWord, INT8U *buff, INT32U mdigit, INT8U ch);
void UTL_Byte2Hex(INT8U byte, INT8U *buff);
void UTL_Word2Hex(INT16U word, INT8U *buff);
void UTL_Long2Hex(INT32U dword, INT8U *buff);
INT8U UTL_Byte2Bcd(INT8U byte);
INT8U UTL_Bcd2Byte(INT8U bcd);
void UTL_Bcd2Ascii(INT8U bcd, INT8U *buff);
INT8U UTL_IsDigitAscii(INT8U digit);
INT8U UTL_IsXDigitAscii(INT8U digit);
INT16U UTL_WordDelta(INT16U v1, INT16U v2);
INT8U UTL_ByteDelta(INT8U v1, INT8U v2);
INT8U UTL_Word2Float(INT16U word, INT8U *buff, INT8U deci);
INT8U UTL_Long2Float(INT32U LongWord, INT8U *buff, INT8U deci);
INT32U UTL_StrLen(INT8U *str);
INT32U UTL_IsBCD(INT8U *buff, INT32U len);
INT32U UTL_MemCmp(INT8U *ptr1, INT8U *ptr2, INT32U len);
void UTL_MemCpy(INT8U *d, INT8U *s, INT32U len);

INT32U XXTEAEncode(const INT8U *pInputBuffer,
                   INT8U *pOutputBuffer,
                   INT32U nLength,
                   INT32U *pUserDefineKey);
INT8U XXTEADecode(const INT8U *pInputBuffer,
                  INT8U *pOutputBuffer,
                  INT32U nLength,
                  INT32U *pUserDefineKey);
INT16U CRC16_All(INT8U *pbuffer, INT16U length);
INT16U CRC16_Single(INT16U crc, INT8U data);
INT16U CRC16_Result(INT16U crc);
INT8U CheckEndian(void);
INT32U CovToInt32(FP32 f32_data);
INT16U CRC16_Calculate(INT16U u16_CRC, INT8U *pbuffer, INT16U length);

#endif

