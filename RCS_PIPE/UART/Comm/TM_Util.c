/*******************************************************************************

     ARM7 Time Delay Utility

   (C) Copyright 2006, RAE Systems Inc.      All rights reserved

--------------------------------------------------------------------------------

     File name: TM_util.C
      Hardware: ARM7TDMI
     Reference:

--------------------------------------------------------------------------------

   == Important Note ==

   . The time functions do not use any hardware timer, therefore the time delay
     is not precise especially when interrupts are used.

   . See header file for definition of delay constant.   The DELAY_x works in
     both Arm mode and Thumb mode.

--------------------------------------------------------------------------------

   Revision History

   == V1.00.00 ==
      Mar. 27, 2006 - copy from TM_util.c

   == V1.00.01 ==
      07/13/06 - Wenpeng, review and VSS

   == V1.00.02 ==
      08/19/06 - Wenpeng, add TypeDef support

*******************************************************************************/


#include "includes.h"
/* 毫秒级 延时 */
void ms_sleep(int ms)
{
	struct timeval delay;
	delay.tv_sec = 0;
	delay.tv_usec = ms * 1000; // 20 ms
	select(0, NULL, NULL, NULL, &delay);

}

void TM_Delay(INT32U delay)
{
    ms_sleep(delay);
}


INT32U TM_Check(INT32U count, INT32U(*check)(void))
{
    count *= 4;
    while (count--) {
        if (check() == 1) {
            return 1;    // reach condition
        }
    }
    return 0;                                    // Timeout
}

