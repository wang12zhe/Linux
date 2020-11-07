#include"includes.h"

void ShowTime()   
{   
    time_t now; //实例化time_t结构    
    struct tm *timenow; //实例化tm结构指针    
    time(&now);   
    //time函数读取现在的时间(国际标准时间非北京时间)，然后传值给now    
    
    timenow = localtime(&now);   
    //localtime函数把从time取得的时间now换算成你电脑中的时间(就是你设置的地区)    
    
    printf("Local time is %s \n",asctime(timenow));   
    //上句中asctime函数把时间转换成字符，通过printf()函数输出    
} 
