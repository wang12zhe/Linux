
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
 
struct Command{
    unsigned char Index;
    unsigned char Description[30];
    void (*fp_Action)(int fd, unsigned char send_buf[],unsigned int len);
};

void Action(int fd, unsigned char send_buf[],unsigned int len){
    len = UART0_Send(fd,send_buf,len);
}

struct Command Cmd[] ={
{'A',"111111111111",Action},
{'B',"BBBBBBBBBBBB",Action},
{'C',"CCCCCCCCCCCC",Action},
};

void SendData(void *arg){

   char ReadStr[50];
   unsigned int ComdLen = sizeof(Cmd)/sizeof(Cmd[0]);
   unsigned int i=0,j=0;
   int fd = *(int *)arg;
    while(1){
        fgets(ReadStr,50,stdin);
        j =0;
        if(strlen(ReadStr) > 0){
            while(ReadStr[j]){
                for(i =0;i < ComdLen;i++){
                    if (ReadStr[j] == Cmd[i].Index){
                        Cmd[i].fp_Action(fd,Cmd[i].Description,strlen(Cmd[i].Description));  
                        break;  
                    }
                }
                j ++;
            }
        }else{
            sleep(1);
        }
    }
}
void Receive (void *arg){
    char len=0;
    char rcv_buf[256];
    int fd = *(int *)arg;
    while (1) {  //循环读取数据
        memset(rcv_buf,0,256);      
        len = UART0_Recv(fd, rcv_buf,sizeof(rcv_buf)); 
        if(len > 0){    
            rcv_buf[len] = '\0';    
            printf("receive data is %s\n",rcv_buf); 
        }    
        else{     
        }                   
    }
}
//start gdbserver on linux gdbserver localhost:1234 /home/a123/UART/usart /dev/ttyS0
int main(int argc, char **argv)    
{
	int fd = -1;           //文件描述符，先定义一个与程序无关的值，防止fd为任意值导致程序出bug    
    int err;               //返回调用函数的状态    
    int len;                            
    int i;    
    pthread_t	ntid1,ntid2;
             
    if(argc != 2)    
    {  
        printf("=========================\n");  
        printf("Usage: %s /dev/ttyS0     \n",argv[0]);
        printf("=========================\n");
        return FALSE;    
    }    
     fd = UART0_Open(fd,argv[1]); //打开串口，返回文件描述符   
     printf("iiiiiiiiiii-%d",fd);
     do{    
        err = UART0_Init(fd,115200,0,8,1,'N');    
        printf("Set Port Exactly!\n"); 
        sleep(1);   
    }while(FALSE == err || FALSE == fd);    


	err = pthread_create(&ntid1, NULL, (void *)SendData, (&fd));
	if (err != 0){
        perror("can't create thread");     
    }

    err = pthread_create(&ntid2, NULL, (void *)Receive, (&fd));
	if (err != 0){
        perror("can't create thread");     
    }

pthread_join(ntid1,NULL);
pthread_join(ntid2,NULL);
} 
