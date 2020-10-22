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

#if defined( OSC_11059200 )
#define DELAY_5US          13
#define DELAY_10US         27
#define DELAY_100US        275
#define DELAY_200US        552
#define DELAY_300US        828
#define DELAY_400US        1105
#define DELAY_500US        1381
#define DELAY_600US        1658
#define DELAY_700US        1934
#define DELAY_800US        2211
#define DELAY_900US        2487
#define DELAY_1MS          2764
#define DELAY_2MS          5529
#define DELAY_3MS          8293
#define DELAY_4MS          11058
#define DELAY_5MS          13823
#define DELAY_6MS          16588
#define DELAY_7MS          19353
#define DELAY_8MS          22117
#define DELAY_9MS          24882
#define DELAY_10MS         27647
#define DELAY_20MS         55295
#define DELAY_30MS         82943
#define DELAY_40MS         110592
#define DELAY_50MS         138239
#define DELAY_60MS         165887
#define DELAY_70MS         193535
#define DELAY_80MS         221183
#define DELAY_90MS         248831
#define DELAY_100MS        276479
#define DELAY_1SEC         2764799
#elif defined( OSC_12000000 )
#define DELAY_5US          14
#define DELAY_10US         29
#define DELAY_100US        299
#define DELAY_200US        599
#define DELAY_300US        899
#define DELAY_400US        1199
#define DELAY_500US        1499
#define DELAY_600US        1799
#define DELAY_700US        2099
#define DELAY_800US        2399
#define DELAY_900US        2699
#define DELAY_1MS          2999
#define DELAY_2MS          5999
#define DELAY_3MS          8999
#define DELAY_4MS          11999
#define DELAY_5MS          14999
#define DELAY_6MS          17999
#define DELAY_7MS          20999
#define DELAY_8MS          23999
#define DELAY_9MS          26999
#define DELAY_10MS         29999
#define DELAY_20MS         59999
#define DELAY_30MS         89999
#define DELAY_40MS         119999
#define DELAY_50MS         149999
#define DELAY_60MS         179999
#define DELAY_70MS         209999
#define DELAY_80MS         239999
#define DELAY_90MS         269999
#define DELAY_100MS        299999
#define DELAY_1SEC         2999999
#else                      // default is 11.0592 MHz
#define DELAY_5US          13
#define DELAY_10US         27
#define DELAY_100US        275
#define DELAY_200US        552
#define DELAY_300US        828
#define DELAY_400US        1105
#define DELAY_500US        1381
#define DELAY_600US        1658
#define DELAY_700US        1934
#define DELAY_800US        2211
#define DELAY_900US        2487
#define DELAY_1MS          2764
#define DELAY_2MS          5529
#define DELAY_3MS          8293
#define DELAY_4MS          11058
#define DELAY_5MS          13823
#define DELAY_6MS          16588
#define DELAY_7MS          19353
#define DELAY_8MS          22117
#define DELAY_9MS          24882
#define DELAY_10MS         27647
#define DELAY_20MS         55295
#define DELAY_30MS         82943
#define DELAY_40MS         110592
#define DELAY_50MS         138239
#define DELAY_60MS         165887
#define DELAY_70MS         193535
#define DELAY_80MS         221183
#define DELAY_90MS         248831
#define DELAY_100MS        276479
#define DELAY_1SEC         2764799
#endif


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
