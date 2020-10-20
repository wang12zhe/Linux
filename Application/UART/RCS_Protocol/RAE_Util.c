/*******************************************************************************

     RAE Utility

   (C) Copyright 2006, RAE Systems Inc.      All rights reserved

--------------------------------------------------------------------------------

     File name: RAE_util.C
      Hardware: ARM7
     Reference:

--------------------------------------------------------------------------------

   == Important Note ==

--------------------------------------------------------------------------------

   Revision History

   == V1.00.00 ==
      10/29/06 - Wenpeng,

*******************************************************************************/

#include "includes.h"


static void (*Reset)(void) = (void (*)(void))0x00000000;


/*
INT32U UTL_GetAverageRaw( INT16U (*pFunc)( INT8U ), INT8U u8_ch )
{
   INT32U i, temp, max1, max2, min1, min2, sum;

   sum = 0;
   min1 = 0xFFFF;
   max1 = 0;
   min2 = 0xFFFF;
   max2 = 0;
   for ( i=0; i<20; i++ ) {
      temp = (*pFunc)( u8_ch );
      if ( temp > max1 ) {
         max2 = max1;
         max1 = temp;
      }
      else if ( temp > max2 ) {
         max2 = temp;
      }
      if ( temp < min1 ) {
         min2 = min1;
         min1 = temp;
      }
      else if ( temp < min2 ) {
         min2 = temp;
      }
      sum += temp;
   }
   return (sum - max2 - max1 - min2 - min1)>>4;
}
*/


INT32U UTL_GetAverageRaw(INT16U(*pFunc)(INT8U), INT8U u8_ch)
{
    INT32U i, temp, max, min, sum;

    sum = 0;
    min = 0xFFFFFFFF;
    max = 0;
    for (i = 0; i < 10; i++) {
        temp = (*pFunc)(u8_ch);
        if (temp > max) {
            max = temp;
        }
        if (temp < min) {
            min = temp;
        }
        sum += temp;
    }
    return (sum - max - min) >> 3;
}


INT8U UTL_CalChkSum8to8(INT8U *buff, INT32U len)
{
    INT8U sum = 0;
    INT32U i = 0;

    while (i < len) {
        sum += buff[i++];
    }
    sum = 1 + ~sum;

    return sum;
}

INT8U UTL_CheckSum8(INT8U *u8p_Ptr, INT32U u32_Len)
{
    INT32U i;
    INT8U sum = 0;

    for (i = 0; i < u32_Len; i++, u8p_Ptr++) {
        sum += *(u8p_Ptr);
    }
    return sum;
}


INT32U UTL_CheckSum32(INT32U *u32p_Ptr, INT32U u32_Len)
{
    INT32U i, sum = 0;

    for (i = 0; i < u32_Len; i++, u32p_Ptr++) {
        sum += *(u32p_Ptr);
    }
    return sum;
}

INT32U VerifyCheckSum8to32(INT8U *buff, INT32U len)
{
    INT32U sum = 0;
    INT32U i = 4;

    while (i < len) {
        sum += buff[i++];
    }
    i = *(INT32U *)buff;
    sum += i;
    return sum;
}

INT32U CalCheckSum8to32(INT8U *buff, INT32U len)
{
    INT32U sum = 0;
    INT32U i = 0;

    while (i < len) {
        sum += buff[i++];
    }
    sum = 1 + ~sum;
    return sum;
}

INT32U UTL_FindRange(INT32U u32_Num, INT32U *u32p_Table, INT32U u32_Len)
{
    INT32U i;

    for (i = 1; i < u32_Len; i++) {
        if (u32_Num <= u32p_Table[i]) {
            break;
        }
    }
    if (i >= u32_Len) {
        i = u32_Len - 1;
    }
    return i;
}


static const INT16U DaysInMonth[12] = {
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};


INT32U UTL_Date2Minute(INT8U *Date)
{
    INT32U min = 0, tmp;

    tmp = UTL_Bcd2Byte(*(Date));                       // 3G#00003
    min = tmp * 365 * 24 * 60;
    tmp = UTL_Bcd2Byte(*(Date + 1)) - 1;               // 3G#00003
    min += DaysInMonth[tmp] * 24 * 60;
    tmp = UTL_Bcd2Byte(*(Date + 2)) - 1;               // 3G#00003
    min += tmp * 24 * 60;
    tmp = UTL_Bcd2Byte(*(Date + 3));                   // 3G#00003
    min += tmp * 60;
    tmp = UTL_Bcd2Byte(*(Date + 4));                   // 3G#00003
    min += tmp;
    return min;
}


static const INT32U Power[10] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
};


INT8U UTL_Byte2Deci(INT8U byte, INT8U *buff)
{
    INT8U temp, i = 0;

    temp = byte / 100;
    if (temp) {
        *(buff + i++) = temp + '0';
    }
    byte = byte % 100;
    temp = byte / 10;
    if (i || temp) {
        *(buff + i++) = temp + '0';
    }
    temp = byte % 10;
    *(buff + i++) = temp + '0';
    *(buff + i) = '\0';
    return i;
}


void UTL_Byte2DeciS(INT8U byte, INT8U *buff, INT8U ch)
{
    INT8U temp, i = 0, flag = 0;

    temp = byte / 100;
    if (temp) {
        *(buff + i++) = temp + '0';
        flag = 1;
    }
    else {
        *(buff + i++) = ch;
    }
    byte = byte % 100;
    temp = byte / 10;
    if (flag || temp) {
        *(buff + i++) = temp + '0';
    }
    else {
        *(buff + i++) = ch;
    }
    temp = byte % 10;
    *(buff + i++) = temp + '0';
    *(buff + i) = '\0';
}


INT8U UTL_Word2Deci(INT16U word, INT8U *buff)
{
    INT8U temp, i;

    i = 0;
    temp = word / 10000;
    word = word % 10000;
    if (temp) {
        *(buff + i++) = temp + '0';
    }

    temp = word / 1000;
    word = word % 1000;
    if (i || temp) {
        *(buff + i++) = temp + '0';
    }

    temp = word / 100;
    word = word % 100;
    if (i || temp) {
        *(buff + i++) = temp + '0';
    }

    temp = word / 10;
    word = word % 10;
    if (i || temp) {
        *(buff + i++) = temp + '0';
    }

    *(buff + i++) = word + '0';
    *(buff + i) = '\0';
    return i;
}


void UTL_Word2DeciS(INT16U word, INT8U *buff, INT8U ch)
{
    INT8U temp, i, flag = 0;

    i = 0;
    temp = word / 10000;
    word = word % 10000;
    if (temp) {
        *(buff + i++) = temp + '0';
        flag = 1;
    }
    else {
        *(buff + i++) = ch;
    }

    temp = word / 1000;
    word = word % 1000;
    if (flag || temp) {
        *(buff + i++) = temp + '0';
        flag = 1;
    }
    else {
        *(buff + i++) = ch;
    }

    temp = word / 100;
    word = word % 100;
    if (flag || temp) {
        *(buff + i++) = temp + '0';
        flag = 1;
    }
    else {
        *(buff + i++) = ch;
    }

    temp = word / 10;
    word = word % 10;
    if (flag || temp) {
        *(buff + i++) = temp + '0';
    }
    else {
        *(buff + i++) = ch;
    }

    *(buff + i++) = word + '0';
    *(buff + i) = '\0';
}


INT32U UTL_Long2Deci(INT32U qbyte, INT8U *buff, INT32U mdigit)
{
    INT8U temp;
    INT32U i, k;

    i = 0;
    for (k = mdigit - 1; k; k--) {
        temp = qbyte / Power[k];
        qbyte = qbyte % Power[k];
        if (i || temp) {
            *(buff + i++) = temp + '0';
        }
    }
    *(buff + i++) = qbyte + '0';
    *(buff + i) = '\0';
    return i;
}


void UTL_Long2DeciS(INT32U qbyte, INT8U *buff, INT32U mdigit, INT8U ch)
{
    INT8U temp;
    INT32U i, flag, k;

    i = 0;
    flag = 0;
    for (k = mdigit - 1; k; k--) {
        temp = qbyte / Power[k];
        qbyte = qbyte % Power[k];
        if (flag || temp) {
            *(buff + i++) = temp + '0';
            flag = 1;
        }
        else {
            *(buff + i++) = ch;
        }
    }

    *(buff + i++) = qbyte + '0';
    *(buff + i) = '\0';
}


static INT8U btoh(INT8U num)
{
    num = num & 0x0F;
    return (num < 10) ? num + '0' : num - 10 + 'A';
}


void UTL_Byte2Hex(INT8U byte, INT8U *buff)
{
    *buff++ = btoh(byte >> 4);
    *buff++ = btoh(byte);
    *buff = '\0';
}


void UTL_Word2Hex(INT16U word, INT8U *buff)
{
    *buff++ = btoh((INT8U)(word >> 12));
    *buff++ = btoh((INT8U)(word >> 8));
    *buff++ = btoh((INT8U)(word >> 4));
    *buff++ = btoh((INT8U)(word));
    *buff = '\0';
}


void UTL_Long2Hex(INT32U dword, INT8U *buff)
{
    *buff++ = btoh((INT8U)(dword >> 28));
    *buff++ = btoh((INT8U)(dword >> 24));
    *buff++ = btoh((INT8U)(dword >> 20));
    *buff++ = btoh((INT8U)(dword >> 16));
    *buff++ = btoh((INT8U)(dword >> 12));
    *buff++ = btoh((INT8U)(dword >> 8));
    *buff++ = btoh((INT8U)(dword >> 4));
    *buff++ = btoh((INT8U)(dword));
    *buff = '\0';
}


INT8U UTL_Byte2Bcd(INT8U byte)
{
    return (byte % 10) | (((byte / 10) % 10) << 4);
}


INT8U UTL_Bcd2Byte(INT8U bcd)
{
    return (bcd & 0x0F) + ((bcd >> 4) * 10);
}


void UTL_Bcd2Ascii(INT8U bcd, INT8U *buff)
{
    *buff++ = (bcd >> 4) + '0';
    *buff++ = (bcd & 0xF) + '0';
    *buff = '\0';
}

INT8U UTL_IsDigitAscii(INT8U digit)
{
    return (((digit >= '0') && (digit <= '9')) ? digit : 0);
}

INT8U UTL_IsXDigitAscii(INT8U digit)
{
    if (((digit >= 'a') && (digit <= 'f')) || \
            ((digit >= 'A') && (digit <= 'F'))) {
        return (digit);
    }
    else if (UTL_IsDigitAscii(digit)) {
        return (digit);
    }
    else {
        return (0);
    }
}

INT16U UTL_WordDelta(INT16U v1, INT16U v2)
{
    return (v1 > v2) ? (v1 - v2) : (v2 - v1);
}


INT8U UTL_ByteDelta(INT8U v1, INT8U v2)
{
    return (v1 > v2) ? (v1 - v2) : (v2 - v1);
}


INT8U UTL_Word2Float(INT16U word, INT8U *buff, INT8U deci)
{
    INT8U len, i, p;

    len = UTL_Word2Deci(word, buff);
    if (deci) {
        if (len == deci) {
            for (i = 0; i <= deci; i++) {
                p = len - i;
                *(buff + p + 2) = *(buff + p);
            }
            *buff = '0';
            *(buff + 1) = '.';
            return (len + 2);
        }
        else if (len < deci) {
            for (i = 0; i <= len; i++) {
                p = len - i;
                *(buff + p + deci) = *(buff + p);
            }
            for (i = (deci - len); i >= 1; i--) {
                *(buff + i + 1) = '0';
            }
            *buff = '0';
            *(buff + 1) = '.';
            return (deci + 2);
        }
        else {
            for (i = 0; i <= deci; i++) {
                p = len - i;
                *(buff + p + 1) = *(buff + p);
            }
            *(buff + len - deci) = '.';
            return (len + 1);
        }
    }
    return len;
}


INT8U UTL_Long2Float(INT32U qbyte, INT8U *buff, INT8U deci)
{
    INT8U len, i, p;

    len = UTL_Long2Deci(qbyte, buff, 10);
    if (deci) {
        if (len == deci) {
            for (i = 0; i <= deci; i++) {
                p = len - i;
                *(buff + p + 2) = *(buff + p);
            }
            *buff = '0';
            *(buff + 1) = '.';
            return (len + 2);
        }
        else if (len < deci) {
            for (i = 0; i <= len; i++) {
                p = len - i;
                *(buff + p + deci) = *(buff + p);
            }
            for (i = (deci - len); i >= 1; i--) {
                *(buff + i + 1) = '0';
            }
            *buff = '0';
            *(buff + 1) = '.';
            return (deci + 2);
        }
        else {
            for (i = 0; i <= deci; i++) {
                p = len - i;
                *(buff + p + 1) = *(buff + p);
            }
            *(buff + len - deci) = '.';
            return (len + 1);
        }
    }
    return len;
}


INT32U UTL_StrLen(INT8U *str)
{
    INT32U i;

    for (i = 0; *str++ != '\0'; i++);
    return i;
}


INT32U UTL_IsBCD(INT8U *buff, INT32U len)
{
    INT32U i;
    INT8U msb, lsb;

    for (i = 0; i < len; i++, buff++) {
        msb = (*buff) >> 4;
        lsb = (*buff) & 0x0F;
        if (msb > 0x09 || lsb > 0x09) {
            return 0;
        }
    }
    return 1;
}


INT32U UTL_MemCmp(INT8U *ptr1, INT8U *ptr2, INT32U len)
{
    INT32U i;

    for (i = 0; i < len; i++) {
        if (*ptr1++ != *ptr2++) {
            return 0;
        }
    }
    return 1;
}


void UTL_MemCpy(INT8U *d, INT8U *s, INT32U len)
{
    INT32U i;

    for (i = 0; i < len; i++) {
        *d++ = *s++;
    }
}

// CRC-16: x16 + x15 + x2 + 1, 0x8005
#define CRC16_POLY          0x8005
#define CRC16_INIT_REM      0x0000
#define CRC16_FINAL_XOR     0x0000
#define CRC_TABLE_SIZE      256

const unsigned short crc16Table[CRC_TABLE_SIZE] = {
    0x0000, 0x8005, 0x800F, 0x000A,
    0x801B, 0x001E, 0x0014, 0x8011,
    0x8033, 0x0036, 0x003C, 0x8039,
    0x0028, 0x802D, 0x8027, 0x0022,
    0x8063, 0x0066, 0x006C, 0x8069,
    0x0078, 0x807D, 0x8077, 0x0072,
    0x0050, 0x8055, 0x805F, 0x005A,
    0x804B, 0x004E, 0x0044, 0x8041,
    0x80C3, 0x00C6, 0x00CC, 0x80C9,
    0x00D8, 0x80DD, 0x80D7, 0x00D2,
    0x00F0, 0x80F5, 0x80FF, 0x00FA,
    0x80EB, 0x00EE, 0x00E4, 0x80E1,
    0x00A0, 0x80A5, 0x80AF, 0x00AA,
    0x80BB, 0x00BE, 0x00B4, 0x80B1,
    0x8093, 0x0096, 0x009C, 0x8099,
    0x0088, 0x808D, 0x8087, 0x0082,
    0x8183, 0x0186, 0x018C, 0x8189,
    0x0198, 0x819D, 0x8197, 0x0192,
    0x01B0, 0x81B5, 0x81BF, 0x01BA,
    0x81AB, 0x01AE, 0x01A4, 0x81A1,
    0x01E0, 0x81E5, 0x81EF, 0x01EA,
    0x81FB, 0x01FE, 0x01F4, 0x81F1,
    0x81D3, 0x01D6, 0x01DC, 0x81D9,
    0x01C8, 0x81CD, 0x81C7, 0x01C2,
    0x0140, 0x8145, 0x814F, 0x014A,
    0x815B, 0x015E, 0x0154, 0x8151,
    0x8173, 0x0176, 0x017C, 0x8179,
    0x0168, 0x816D, 0x8167, 0x0162,
    0x8123, 0x0126, 0x012C, 0x8129,
    0x0138, 0x813D, 0x8137, 0x0132,
    0x0110, 0x8115, 0x811F, 0x011A,
    0x810B, 0x010E, 0x0104, 0x8101,
    0x8303, 0x0306, 0x030C, 0x8309,
    0x0318, 0x831D, 0x8317, 0x0312,
    0x0330, 0x8335, 0x833F, 0x033A,
    0x832B, 0x032E, 0x0324, 0x8321,
    0x0360, 0x8365, 0x836F, 0x036A,
    0x837B, 0x037E, 0x0374, 0x8371,
    0x8353, 0x0356, 0x035C, 0x8359,
    0x0348, 0x834D, 0x8347, 0x0342,
    0x03C0, 0x83C5, 0x83CF, 0x03CA,
    0x83DB, 0x03DE, 0x03D4, 0x83D1,
    0x83F3, 0x03F6, 0x03FC, 0x83F9,
    0x03E8, 0x83ED, 0x83E7, 0x03E2,
    0x83A3, 0x03A6, 0x03AC, 0x83A9,
    0x03B8, 0x83BD, 0x83B7, 0x03B2,
    0x0390, 0x8395, 0x839F, 0x039A,
    0x838B, 0x038E, 0x0384, 0x8381,
    0x0280, 0x8285, 0x828F, 0x028A,
    0x829B, 0x029E, 0x0294, 0x8291,
    0x82B3, 0x02B6, 0x02BC, 0x82B9,
    0x02A8, 0x82AD, 0x82A7, 0x02A2,
    0x82E3, 0x02E6, 0x02EC, 0x82E9,
    0x02F8, 0x82FD, 0x82F7, 0x02F2,
    0x02D0, 0x82D5, 0x82DF, 0x02DA,
    0x82CB, 0x02CE, 0x02C4, 0x82C1,
    0x8243, 0x0246, 0x024C, 0x8249,
    0x0258, 0x825D, 0x8257, 0x0252,
    0x0270, 0x8275, 0x827F, 0x027A,
    0x826B, 0x026E, 0x0264, 0x8261,
    0x0220, 0x8225, 0x822F, 0x022A,
    0x823B, 0x023E, 0x0234, 0x8231,
    0x8213, 0x0216, 0x021C, 0x8219,
    0x0208, 0x820D, 0x8207, 0x0202
};

INT16U CRC16_All(INT8U *pbuffer, INT16U length)
{
    INT16U crc = CRC16_INIT_REM;

    while (length--) {
        crc = crc16Table[((crc >> 8) ^ *pbuffer++)] ^ (crc << 8);    // normal
    }
    return (crc ^ CRC16_FINAL_XOR);
}


INT16U CRC16_Single(INT16U crc, INT8U data)
{
    crc = crc16Table[((crc >> 8) ^ data)] ^ (crc << 8);
    return (crc);
}

INT16U CRC16_Result(INT16U crc)
{
    return (crc ^ CRC16_FINAL_XOR);
}
INT16U CRC16_Calculate(INT16U u16_CRC, INT8U *pbuffer, INT16U length)
{
    INT16U crc = u16_CRC;
    while (length--) {
        crc = crc16Table[((crc >> 8) ^ *pbuffer++)] ^ (crc << 8);    // normal
    }
    return crc;
}

#define DELTA    0x9e3779b9
#define MX        (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))

void btea(INT32U *v, INT32S n, INT32U key[4])
{
    INT32U y, z, sum;
    INT32U p, rounds, e;

    if (n > 1) {
        /* Coding Part */
        rounds = 6 + 52 / n;
        sum = 0;
        z = v[n - 1];
        do {
            sum += DELTA;
            e = (sum >> 2) & 3;
            for (p = 0; p < n - 1; p++) {
                y = v[p + 1];
                z = v[p] += MX;
            }
            y = v[0];
            z = v[n - 1] += MX;
        }
        while (--rounds);
    }
    else if (n < -1) {
        /* Decoding Part */
        n = -n;
        rounds = 6 + 52 / n;
        sum = rounds * DELTA;
        y = v[0];
        do {
            e = (sum >> 2) & 3;
            for (p = n - 1; p > 0; p--) {
                z = v[p - 1];
                y = v[p] -= MX;
            }
            z = v[n - 1];
            y = v[0] -= MX;
        }
        while ((sum -= DELTA) != 0);
    }
}

#define XXTEA_ALIGNMENT_BYTES    4
INT32U XXTEAEncode(const INT8U *pInputBuffer,
                   INT8U *pOutputBuffer,
                   INT32U nLength,
                   INT32U *pUserDefineKey)
{
    INT32U nResult = 0;
    nResult = nLength / XXTEA_ALIGNMENT_BYTES + (nLength % XXTEA_ALIGNMENT_BYTES ? 1 : 0);
    if (pInputBuffer && pOutputBuffer && nResult) {
        //memset(pOutputBuffer, 0xFF, nResult * XXTEA_ALIGNMENT_BYTES);
        memcpy(pOutputBuffer, pInputBuffer, nLength);
        btea((INT32U *)pOutputBuffer, nResult, pUserDefineKey);
    }
    nResult *= XXTEA_ALIGNMENT_BYTES;
    return nResult;
}


INT8U XXTEADecode(const INT8U *pInputBuffer,
                  INT8U *pOutputBuffer,
                  INT32U nLength,
                  INT32U *pUserDefineKey)
{
    INT8U result = FALSE;

    if ((nLength == 0) || (nLength % XXTEA_ALIGNMENT_BYTES)) {
        return FALSE;
    }

    if (pInputBuffer && pOutputBuffer && nLength) {
        INT32S nSize = (nLength / XXTEA_ALIGNMENT_BYTES);
        //memset(pOutputBuffer, 0xFF, 256);
        memcpy(pOutputBuffer, pInputBuffer, nLength);
        btea((INT32U *)pOutputBuffer, -nSize, pUserDefineKey);
        result = TRUE;
    }
    return result;
}
