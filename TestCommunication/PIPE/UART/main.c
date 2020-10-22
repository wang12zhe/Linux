
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
 

#include "includes.h"
pthread_mutex_t mut;
unsigned char RetryFlag =0;
unsigned char ReceFlag =0;
struct Command{
    unsigned char Index;
    unsigned char Description[30];
    void (*fp_Action)(void);
};

int fdwr =-1;
int fdrd =-1;
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
{'A',"111111111111",Sensor_Init}
};

void ParserCommand(int fdwr,int fdrd){

   char ReadStr[50];
   unsigned int ComdLen = sizeof(Cmd)/sizeof(Cmd[0]);
   unsigned int i=0;
   char *len;
   unsigned char j=0;
   SCDC_SensorResp_Init(fdrd);
   SCDC_SensorHost_Init(fdwr);
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
                        Cmd[i].fp_Action();
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

        // if(wait(NULL) ==-1){ //回收子进程状态，避免僵尸进程
        //     perror("fail to wait\n");
        //     exit(1);
        // }
        // printf("child has been killed.\n");
    }
}

void ReadData(int signal_no){
    int len =0;
    unsigned char buff[255];
    if(signal_no == SIGUSR1){
        len = read(fdrd,buff,sizeof(buff)/sizeof(buff[0]));
        printf("Father Get data len  =%d \n",len);
        if(len > 0){
            printf("Father get data :%s \n",buff);   
        }
    }
}

void CatchCrash(int signal_no){
  int status;  
  while(waitpid(-1, &status, WNOHANG) > 0);
}

//start gdbserver on linux gdbserver localhost:1234 /home/a123/UART/usart /dev/ttyS0
int main(int argc, char **argv)    
{
    char Str1[4];
    char Str2[4];
    pid_t pid;
    pid_t ppid;
    int fd_Write[2];    // Father write child read
    int fd_Read[2];    // Father Read child Write
    if(argc != 1){  
        printf("=========================\n");  
        printf("Usage: %s   \n",argv[0]);
        printf("=========================\n");
        exit(1);   
    } 
    //为两个信号设置信号处理函数
    if(signal(SIGUSR1, ReadData) == SIG_ERR){ //设置出错
        perror("Can't set handler for SIGUSR1\n");
        exit(1);
    }
        //为两个信号设置信号处理函数
    if(signal(SIGCHLD, CatchCrash) == SIG_ERR){ //设置出错
        perror("Can't set handler for SIGCHLD\n");
        exit(1);
    }
    
    if((pipe(fd_Write) < 0)){
        perror("Create First PIPE error!");
        exit(1);
    }
    if((pipe(fd_Read) < 0)){
        perror("Create Sencond PIPE error!");
        exit(1);
    }

    

    if((pid = fork()) <0){
        perror("Fail to fork");
        exit(1);
    }else if(pid > 0){   //Father
        close(fd_Write[0]);   //close Write
        close(fd_Read[1]);    //close read
        printf("fd_Write[1] =  fd_Read[0] =\n");
        printf("fd_Write[1] = %d fd_Read[0] =%d\n",fd_Write[1],fd_Read[0]);
        printf("fd_Write[0] = %d fd_Read[1] =%d\n",fd_Write[0],fd_Read[1]);
        fdrd = fd_Read[0];
        fdwr = fd_Write[1];
        ParserCommand(fd_Write[1],fd_Read[0]);
        exit(0);
    }else{   //Children
        close(fd_Write[1]);   //close Read
        close(fd_Read[0]);    //close read
        ppid = getppid();
        printf("222 PPID =%d \n",ppid);
        prctl(PR_GET_PDEATHSIG , SIGHUP);
        printf("Start ChildRen ！\n");
        printf("fd_Write[0] = %d fd_Read[1] =%d\n",fd_Write[0],fd_Read[1]);
        system("pwd");
        sprintf(Str1,"%d",fd_Write[0]);
        sprintf(Str2,"%d",fd_Read[1]);
        execl("../uartDriver/usart","/dev/ttyS0",Str1,Str2,NULL);
        exit(0);
    }
   
    close(fdrd);
    close(fdwr);
    return 0;
}
// #include <stdio.h>
// #include <sys/types.h>
// #include <unistd.h>
// #include <stdlib.h>

// int main(void)
// {
//     pid_t pid;
 
//     pid = fork();
//     if(pid < 0){
//         perror("Fail to fork");
//         exit(1);
//     }else if(pid == 0){
//         printf("222 PPID = \n");
//     }else{
//        printf("111111 PPID = \n");
//     }
 
//     return 0;
// }
