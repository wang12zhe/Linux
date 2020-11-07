
/*********************************************************************************
 *      Copyright:  (C) 
 *                  All rights reserved.
 *
 *       Filename:  usart_test.c
 *    Description:  UART driver
 *                 
 *        Version:  1.0.0(08/27/2018)
 *         Author:  yanhuan <yanhuanmini@foxmail.com>
 *      ChangeLog:  1, Release initial version on "08/23/2018 17:28:51 PM"
 *                 
 ********************************************************************************/
 
#include "includes.h"

unsigned char RetryFlag =0;
unsigned char ReceFlag =0;
struct Command{
    unsigned char Index;
    unsigned char Description[30];
    void (*fp_Action)(int fd, unsigned char send_buf[],unsigned int len);
};

struct FDStr{
    int Uart_Fd;
    int FIFO_Fdrd;
    int FIFO_Fdwr;
    pid_t ppid;
};


/* 毫秒级 延时 */
void ms_sleep(int ms)
{
	struct timeval delay;
	delay.tv_sec = 0;
	delay.tv_usec = ms * 1000; // 20 ms
	select(0, NULL, NULL, NULL, &delay);

}
void Action(int fd, unsigned char send_buf[],unsigned int len){
    len = UART0_Send(fd,send_buf,len);
}

// struct Command Cmd[] ={
// {'A',"111111111111",Action},
// {'B',"BBBBBBBBBBBB",Action},
// {'C',"CCCCCCCCCCCC",Action},
// };

void SendData(void *arg){
   char i =0;
   unsigned char buff[50];
 //  unsigned int ComdLen = sizeof(Cmd)/sizeof(Cmd[0]);
   int len =0;
   struct FDStr FD = *(struct FDStr *)arg;
   //printf("SendData  FD.FIFO_Fdrd =%d",FD.FIFO_Fdrd);
   
    while(1){
        //printf("FD.FIFO_Fdrd =%d",FD.FIFO_Fdrd);
        len = read(FD.FIFO_Fdrd,buff,sizeof(buff)/sizeof(buff[0]));
        int RetryCnt =1;
    #if DEBUGUART
        DebugUart("TX: \n");

        for(i =0;i < len;i ++){
            DebugUart("%02X ",buff[i]);
        }
    #endif
        if(len > 0){
            UART0_Send(FD.Uart_Fd,buff,len);
        }
    }
    printf("OUT  \n");
}
void Receive (void *arg){
    char len=0;
    char i =0;
    unsigned char rcv_buf[256];
    struct FDStr FD = *(struct FDStr *)arg;
    while (1) {  //循环读取数据
        bzero(rcv_buf,256); 
   
        len = read(FD.Uart_Fd, rcv_buf,sizeof(rcv_buf)); 

        ReceFlag =1;
        if(len > 0){    
        #if DEBUGUART
            DebugUart("\nRX:\n");
            for(i =0;i < len;i ++){
                DebugUart("%02X ",rcv_buf[i]);
            }
            fflush(stdout);
        #endif
            
            write(FD.FIFO_Fdwr,rcv_buf, len);    
        }    
        else{  
        }                   
    }
}
//start gdbserver on linux: gdbserver localhost:1234 /home/a123/UART/usart /dev/ttyS0
int main(int argc, char **argv)    
{
	int fd = -1;          
    int err;            
    int len;                            
    int i;    
    pthread_t	ntid1,ntid2;
    struct FDStr FD;
    int FIFO_fdwr = -1;
    int FIFO_fdrd = -1;
    pid_t ppid;

    Debug(" \n argc =%d \n",argc);
    Debug("argv 0=%s \n",argv[0]);
    Debug("argv 1=%s \n",argv[1]);
    Debug("argv 2=%s \n",argv[2]); 

    if(argc != 3)    
    {  
        printf("=========================\n");  
        printf("Usage: %s /dev/ttyS0  ReadFD   writeFD\n",argv[0]);
        printf("=========================\n");
        return FALSE;    
    }  
    ppid = getppid();
    Debug("PPID =%d \n",ppid);

     fd = UART0_Open(fd,argv[0]); //打开串口，返回文件描述符   ls 
     if(fd < 0){
         exit(1);
     }
     do{    
        err = UART0_Init(fd,57600,0,8,1,'N');    
        printf("Set Port Exactly!\n"); 
        sleep(1);   
    }while(FALSE == err || FALSE == fd);    
	
    FD.Uart_Fd = fd;
    FD.FIFO_Fdrd = atoi(argv[1]);
    FD.FIFO_Fdwr = atoi(argv[2]);
    Debug("FD.FIFO_Fdrd = %d ,FD.FIFO_Fdwr = %d \n",FD.FIFO_Fdrd,FD.FIFO_Fdwr);
    FD.ppid = ppid;
    err = pthread_create(&ntid1, NULL, (void *)SendData, (&FD));
	if (err != 0){
        perror("can't create thread");     
    }

    err = pthread_create(&ntid2, NULL, (void *)Receive, (&FD));
	if (err != 0){
        perror("can't create thread");     
    }

    if(ntid1 !=0) {
        printf("ntid1\n");
        pthread_join(ntid1,NULL);
    }
    if(ntid1 !=0) {
        printf("ntid2\n");
        pthread_join(ntid2,NULL);
    }
    close(fd);

    return 0;
}

