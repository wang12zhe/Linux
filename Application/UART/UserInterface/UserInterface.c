
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

pthread_mutex_t mut;
unsigned char RetryFlag =0;
unsigned char ReceFlag =0;
struct Command{
    unsigned char Index;
    unsigned char Description[30];
    void (*fp_Action)(int fd, unsigned char send_buf[],unsigned int len);
};



/* 毫秒级 延时 */
void mssleep(int ms)
{
	struct timeval delay;
	delay.tv_sec = 0;
	delay.tv_usec = ms * 1000; // 20 ms
	select(0, NULL, NULL, NULL, &delay);

}
void Action(int fd, unsigned char send_buf[],unsigned int len){
    len = write(fd,send_buf,len);
}

struct Command Cmd[] ={
{'A',"111111111111",Action},
{'B',"BBBBBBBBBBBB",Action},
{'C',"CCCCCCCCCCCC",Action},
};

void ParserCommand(int fd){

   char ReadStr[50];
   unsigned int ComdLen = sizeof(Cmd)/sizeof(Cmd[0]);
   unsigned int i=0;
   char *len;
   unsigned char j=0;
    while(1){
        printf("Input command\n");
        len = fgets(ReadStr,50,stdin);
        //printf("Get Data len  =%d \n",*len);
        j =0;
        if(strlen(ReadStr)> 0){
            while(ReadStr[j]){
                for(i =0;i < ComdLen;i++){
                    if (ReadStr[j] == Cmd[i].Index){
                        //pthread_mutex_lock(&mut);
                        Cmd[i].fp_Action(fd,Cmd[i].Description,strlen(Cmd[i].Description));
                        //pthread_mutex_unlock(&mut);
                        j ++;  
                        break;  
                    }
                }
                if(i == ComdLen){
                    j ++;      
                }
            }
        }else{
            sleep(1);
        }
    }
}

//start gdbserver on linux gdbserver localhost:1234 /home/a123/UART/usart /dev/ttyS0
int main(int argc, char **argv)    
{

    mode_t mode =0666;
    int fd =-1;
    if(argc != 2){  
        printf("=========================\n");  
        printf("Usage: %s File Name    \n",argv[0]);
        printf("=========================\n");
        exit(1);   
    } 

    //Create FIFO
    if((mkfifo(argv[1],mode)) < 0){
        perror("Create FIFO eror");
        exit(1);
    }
    printf("Create FIFO  %s  successfully ！ \n",argv[1]);

    pid_t pid;


    if((pid = fork()) <0){
        perror("Fail to fork");
        exit(1);
    }

    if(pid > 0){   //Father
        if((fd = open(argv[1],O_RDWR|O_NONBLOCK)) < 0){
            perror(" Father : Open FIFO error");
            exit(1);
        }
        ParserCommand(fd);
        exit(0);
    }else{   //Children
        printf("Start ChildRen ！\n");
        execl("./../uartDriver/usart","/dev/ttyS0",argv[1],NULL);
        exit(0);
    }


    close(fd);
    return 0;
}

