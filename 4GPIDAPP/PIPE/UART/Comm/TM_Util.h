/*******************************************************************************

     ARM7 Time Delay Utility

   (C) Copyright 2006, RAE Systems Inc.      All rights reserved

--------------------------------------------------------------------------------

     File name: TM_util.H
      Hardware: ARM7TDMI
     Reference:

--------------------------------------------------------------------------------

   == Important Note ==

   . The time functions do not use any hardware timer, therefore the time delay
     is not precise especially when interrupts are used.

   . The DELAY_x works in both Arm mode and Thumb mode.

--------------------------------------------------------------------------------

   Revision History

   == V1.00.00 ==
      Mar. 27, 2006 - copy from TM_util.c

   == V1.00.01 ==
      07/13/06 - Wenpeng, review and VSS

   == V1.00.02 ==
      08/19/06 - Wenpeng, add TypeDef support

*******************************************************************************/
#ifndef __TM_UTIL_H
#define __TM_UTIL_H

/*******************************************************************************

   Delay Constant(N) Definitions for TM_Delay()

      DelayTime = DelayCycles / ClockFrequency

      - in Thumb mode
      DelayCycles = N x 4 + 7
      N = ((DelayTime x ClockFrequency) - 7 )/4

      - in ARM mode
      DelayCycles = N x 4 + 4
      N = ((DelayTime x ClockFrequency) - 4 )/4

   Delay Constants are calculated based on ARM mode, which

      N = (DelayTime x ClockFrequency)/4 - 1

*******************************************************************************/

#define DELAY_100MS          100
#define DELAY_1S          1000




/*******************************************************************************

   Function Prototypes

--------------------------------------------------------------------------------

   TM_Check() provides a way to prevent program from stucking in infinite loop.
   This function causes some delay, but it is worthy if you were using polling
   technique to check certain condition to be reached.

   TM_Check() will continue as long as check() is not TRUE (1) and count is not
   reached.

   The elapsed time of TM_Check() depends heavily on the function check()
   passed to and should be used with caution.

*******************************************************************************/

void TM_Delay(INT32U delay);

INT32U TM_Check(INT32U count, INT32U(*check)(void));

#endif
