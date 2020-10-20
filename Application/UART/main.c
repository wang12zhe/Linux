
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
    pid_t ppid;
    mode_t mode =0666;
    if(argc != 3){  
        printf("=========================\n");  
        printf("Usage: %s Write File Name  Read File name  \n",argv[0]);
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
    if  (access (argv[1] ,0 ) == -1 ){
        //Create FIFO
        if((mkfifo(argv[1],mode| O_APPEND)) < 0){
            perror("C2222222222reate FIFO eror");
            exit(1);
        }
    }
     if  (access (argv[2] ,0 ) == -1 ){
        //Create FIFO
        if((mkfifo(argv[2],mode| O_APPEND)) < 0){
            perror("C2222222222reate FIFO eror");
            exit(1);
        }
    }    
    printf("Create FIFO  %s  successfully ！ \n",argv[1]);

    pid_t pid;

    if((pid = fork()) <0){
        perror("Fail to fork");
        exit(1);
    }

    if(pid > 0){   //Father
        if((fdwr = open(argv[1],O_WRONLY)) < 0){
            perror(" Father : Open Write FIFO error");
            exit(1);
        }
        if((fdrd = open(argv[2],O_RDONLY|O_NONBLOCK)) < 0){
            perror(" Father : Open read FIFO error");
            exit(1);
        }
        
        ParserCommand(fdwr,fdrd);
        exit(0);
    }else{   //Children
        ppid = getppid();
        printf("222 PPID =%d",ppid);
        prctl(PR_SET_PDEATHSIG, SIGHUP);
        printf("Start ChildRen ！\n");
        execl("./uartDriver/usart","/dev/ttyS0",argv[1],argv[2],NULL);
        exit(0);
    }
   
    close(fdrd);
    close(fdwr);
    return 0;
}

