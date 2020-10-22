
/*********************************************************************************
 *      Copyright:  (C) 2018 Yujie
 *                  All rights reserved.
 *
 *       Filename:  usart_test.c
 *    Description:  串口测试
 *                 
 *        Version:  1.0.0(08/27/2018)
 *         Author:  yanhuan <yanhuanmini@foxmail.com>
 *      ChangeLog:  1, Release initial version on "08/23/2018 17:28:51 PM"
 *                 
 ********************************************************************************/
 
#include "uart.h"
#include<stdio.h>      /*标准输入输出定义*/    
#include<stdlib.h>     /*标准函数库定义*/    
#include<unistd.h>     /*Unix 标准函数定义*/    
#include<sys/types.h>     
#include<sys/stat.h>       
#include<fcntl.h>      /*文件控制定义*/    
#include<termios.h>    /*PPSIX 终端控制定义*/    
#include<errno.h>      /*错误号定义*/    
#include<string.h>
#include <pthread.h>
#include <signal.h>

pthread_mutex_t mut;
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

struct Command Cmd[] ={
{'A',"111111111111",Action},
{'B',"BBBBBBBBBBBB",Action},
{'C',"CCCCCCCCCCCC",Action},
};

void SendData(void *arg){

   char buff[50];
   unsigned int ComdLen = sizeof(Cmd)/sizeof(Cmd[0]);
   int len =0;
   struct FDStr FD = *(struct FDStr *)arg;
   printf("SendData  FD.FIFO_Fdrd =%d",FD.FIFO_Fdrd);
   
    while(1){
        printf("FD.FIFO_Fdrd =%d",FD.FIFO_Fdrd);
        len = read(FD.FIFO_Fdrd,buff,sizeof(buff)/sizeof(buff[0]));
        int RetryCnt =1;
        printf("Read data len =%d \n",len);
        if(len > 0){
            do{
                UART0_Send(FD.Uart_Fd,buff,len);
                ReceFlag =1;
                unsigned char Wait =0;
                while(Wait < 100){
                    if(ReceFlag == 0){
                        RetryCnt =0;
                        break;
                    }else{
                        ms_sleep(10); //10Ms
                        Wait ++;
                    }
                }
                RetryCnt --;
            }while(RetryCnt > 0);
        }
    }

    printf("OUT  \n");
}
void Receive (void *arg){
    char len=0;
    char rcv_buf[256];
    struct FDStr FD = *(struct FDStr *)arg;
    while (1) {  //循环读取数据
        memset(rcv_buf,0,256);      
        len = UART0_Recv(FD.Uart_Fd, rcv_buf,sizeof(rcv_buf)); 
        ReceFlag =1;
        if(len > 0){    
            rcv_buf[len] = '\0'; 
            write(FD.FIFO_Fdwr,rcv_buf, len +1);   
            printf("receive data is %s\n",rcv_buf);
            RetryFlag =0;
            if(kill(FD.ppid, SIGUSR1) == -1){
                perror("fail to send signal\n");
                exit(1);
            } 
        }    
        else{  
            RetryFlag =1;  
        }                   
    }
}
//start gdbserver on linux: gdbserver localhost:1234 /home/a123/UART/usart /dev/ttyS0
int main(int argc, char **argv)    
{
	int fd = -1;           //文件描述符，先定义一个与程序无关的值，防止fd为任意值导致程序出bug    
    int err;               //返回调用函数的状态    
    int len;                            
    int i;    
    pthread_t	ntid1,ntid2;
    struct FDStr FD;
    int FIFO_fdwr = -1;
    int FIFO_fdrd = -1;
    pid_t ppid;

    printf(" \n argc =%d \n",argc);
    printf("argv 0=%s \n",argv[0]);
    printf("argv 1=%s \n",argv[1]);
    printf("argv 2=%s \n",argv[2]); 

    if(argc != 3)    
    {  
        printf("=========================\n");  
        printf("Usage: %s /dev/ttyS0   ReadFifo name   WriteFifo name3\n",argv[0]);
        printf("=========================\n");
        return FALSE;    
    }  
    ppid = getppid();
    printf("111 PPID =%d",ppid);
    // if((FIFO_fdrd = open(argv[1],O_RDONLY)) < 0){
    //     perror(" Father : Open WriteFIFO error");
    //     exit(1);
    // }
    // if((FIFO_fdwr = open(argv[2],O_WRONLY)) < 0){
    //     perror(" Father : Open ReadFIFO error");
    //     exit(1);
    // }

     fd = UART0_Open(fd,argv[0]); //打开串口，返回文件描述符   ls 
     do{    
        err = UART0_Init(fd,57600,0,8,1,'N');    
        printf("Set Port Exactly!\n"); 
        sleep(1);   
    }while(FALSE == err || FALSE == fd);    
    
    pthread_mutex_init(&mut,NULL);
	
    FD.Uart_Fd = fd;
    FD.FIFO_Fdrd = atoi(argv[1]);
    FD.FIFO_Fdwr = atoi(argv[2]);
    printf("FD.FIFO_Fdrd = %d ,FD.FIFO_Fdwr = %d \n",FD.FIFO_Fdrd,FD.FIFO_Fdwr);
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

