#ifndef __SYSFLAG_H__
#define __SYSFLAG_H__

typedef struct {
    INT32U RespGot              : 1;
    INT32U RespError            : 1;
    INT32U NoRespCnt            : 4;
    INT32U CommBusy             : 1;
    INT32U RetryFlag            : 1;
    INT32U                      : 24;
} __sktComFlags_bits;

typedef struct {
    // INT32U_BIT(DevFlags, __devFlags_bits);
    // INT32U_BIT(SelfTestFlags, __selfTestFlags_bits);
    //INT32U_BIT(SysFlags, __sysFlags_bits);
    // INT32U_BIT(SysAlarm, __sysAlarm_bits);
    // INT32U_BIT(RTSysAlarm, __sysAlarm_bits);
    // INT32U_BIT(TimeFlags, __timeFlags_bits);
    INT32U_BIT(SktComFlags, __sktComFlags_bits);
    // INT32U_BIT(WSNComFlags, __sktComFlags_bits);
    // INT32U_BIT(WIFIComFlags, __sktComFlags_bits);
    //   INT32U_BIT(BLEComFlags, __sktComFlags_bits);

} MSG;


#endif