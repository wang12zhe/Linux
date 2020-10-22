/*******************************************************************************

      Data type define

   (C) Copyright 2006, RAE Systems Inc.      All rights reserved

--------------------------------------------------------------------------------

     File name: TypeDef.h
      Hardware: ARM7
     Reference: EWARM_CompilerReference.pdf

--------------------------------------------------------------------------------

   == Important Note ==

   The data type define is extremely hardware and compiler dependent.   If
   target hardware or compiler is changed, this file needs to revise.

--------------------------------------------------------------------------------

   Revision History

   == V1.00.00 ==
      08/16/06 - Wenpeng, review and SVN

*******************************************************************************/


#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__


#ifndef OS_CPU_H                       /* OS_cpu is not included */

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;          /* Unsigned  8 bit quantity       */
typedef signed   char  INT8S;          /* Signed    8 bit quantity       */

typedef unsigned short INT16U;         /* Unsigned 16 bit quantity       */
typedef signed   short INT16S;         /* Signed   16 bit quantity       */

typedef unsigned int   INT32U;         /* Unsigned 32 bit quantity     */
typedef signed   int   INT32S;         /* Signed   32 bit quantity     */

typedef unsigned long long   INT64U;   /* Unsigned 64 bit quantity     */
typedef signed   long long   INT64S;   /* Signed   64 bit quantity     */

typedef float          FP32;           /* Single precision floating point  */
typedef double         FP64;           /* Double precision floating point  */

#endif                                 /* #ifndef OS_CPU_H */

typedef unsigned char *STRING;          /* a null-terminated String */

typedef void (*PFNCT)(void);                    /* function pointer */

#ifndef NULL
#define NULL    ((void *)0)
#endif


#ifndef FALSE
#define FALSE        0
#endif

#ifndef TRUE
#define TRUE         1
#endif

#ifdef true
#undef true
#endif
#define true         1

#ifdef false
#undef false
#endif
#define false        0

#ifdef  DEF_EN
#undef  DEF_EN
#endif
#ifndef DEF_EN
#define DEF_EN          1
#endif

#ifdef  DEF_DIS
#undef  DEF_DIS
#endif
#ifndef DEF_DIS
#define DEF_DIS        0
#endif



#define INT8U_BIT(NAME, BIT_STRUCT)                             \
    union {                                 \
        INT8U NAME;                         \
        BIT_STRUCT NAME ## _bit;        \
    }
#define INT16U_BIT(NAME, BIT_STRUCT)                            \
    union {                                 \
        INT16U NAME;                        \
        BIT_STRUCT NAME ## _bit;        \
    }
#define INT32U_BIT(NAME, BIT_STRUCT)                            \
    union {                                 \
        INT32U NAME;                        \
        BIT_STRUCT NAME ## _bit;        \
    }

#define dim(x) (sizeof(x) / sizeof(x[0])) /* Returns number of elements         */


#endif                                 /* #ifndef __TYPEDEF_H__ */


