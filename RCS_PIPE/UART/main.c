
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

MSG SysMsg;

struct FDStruct{
    int fdwr;
    int fdrd;
};


pthread_mutex_t mutex;
pthread_cond_t cond;


/* 毫秒级 延时 */
void mssleep(int ms)
{
	struct timeval delay;
	delay.tv_sec = 0;
	delay.tv_usec = ms * 1000; // 20 ms
	select(0, NULL, NULL, NULL, &delay);

}





INT8U SendData(struct Command Cmd){
    #define MS_200   250
    SysMsg.SktComFlags_bit.RetryFlag = TRUE;
    unsigned char ReteyCnt =5;
    struct timespec abstime;
    struct timeval now;
    do{
        if(TRUE == SysMsg.SktComFlags_bit.RetryFlag){
            ReteyCnt --;
        }else
        {
            break;
        }
        Cmd.fp_Action(Cmd.Parameter);
        
        gettimeofday(&now, NULL);
        long nsec = now.tv_usec * 1000 + (MS_200 % 1000) * 1000000;  
        abstime.tv_sec = now.tv_sec + nsec / 1000000000 + MS_200 / 1000;
        abstime.tv_nsec=nsec % 1000000000;
        pthread_mutex_lock(&mutex);
        pthread_cond_timedwait(&cond, &mutex, &abstime); 
        pthread_mutex_unlock(&mutex);


    }while(ReteyCnt > 0);

    return (ReteyCnt == 0? FALSE :TRUE);
}



INT8U InitializeSensor(void){
    INT8U i =0;

    for(i =0;i< SensorTableTotal;i ++ ){
        if( FALSE == SendData(SensorTable[i])){
            return FALSE;
        }   
    } 
    return TRUE;  
}

void Mysleep(INT16U time){
    do {
        time = sleep(time);  
    }while(time > 0);
}


void ParserCommand(void *arg){

   char ReadStr[50];
   unsigned int i=0;
   char *len;
   unsigned char j=0;
   struct FDStruct PIPI_fd = *(struct FDStruct *)arg;
   SCDC_SensorResp_Init(PIPI_fd.fdrd);
   SCDC_SensorHost_Init(PIPI_fd.fdwr);
                    pthread_cond_signal(&cond);
   InitializeSensor();
    while(1){
        SHOWTIME;
        SendData(SensorTable[SensorTableTotal -1]);
        sleep(1);
    }
}

void ReadData(void *arg){
    int len =0;
    char i =0;
    char ch;
    RCS_t *rcs;
    unsigned char buff[255];
    int fd = *(int *)arg;
    while(1){
        len = read(fd,buff,sizeof(buff)/sizeof(buff[0]));
        if(len > 0){
            rcs = &SCDC_SensorResp;
            for(i =0;i < len;i ++){
                ch = buff[i];
                RCS_Parser(rcs, ch);
                if (rcs->PacketFlags_bit.PF_ACTION) {
                    RCS_Action( rcs );
                    pthread_cond_signal(&cond);
                    SysMsg.SktComFlags_bit.RetryFlag = FALSE;
                }
            }
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
    int err;  
    pthread_t ntid1,ntid2;
    int fd_Write[2];    // Father write child read
    int fd_Read[2];    // Father Read child Write

    struct FDStruct PIPE_fd;

    if(argc != 2){  
        printf("=========================\n");  
        printf("Usage: %s  %s \n",argv[0],"/dev/ttyxxx");
        printf("=========================\n");
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
        sleep(1);  //等待子进程 先开始运行
        PIPE_fd.fdrd = fd_Read[0];
        PIPE_fd.fdwr = fd_Write[1];
 
        pthread_mutex_init(&mutex, NULL);
	    pthread_cond_init(&cond, NULL);

        //为信号设置信号处理函数
        if(signal(SIGCHLD, CatchCrash) == SIG_ERR){ //设置出错
            perror("Can't set handler for SIGCHLD\n");
            exit(1);
        }

        err = pthread_create(&ntid1, NULL, (void *)ReadData, (&PIPE_fd.fdrd));
        if (err != 0){
            perror("can't create thread");     
        } 
        err = pthread_create(&ntid2, NULL, (void *)ParserCommand, (&PIPE_fd));
        if (err != 0){
            perror("can't create thread");     
        } 
        
        if(ntid1 !=0) {
            printf("Father ntid1\n");
            pthread_join(ntid1,NULL);
        }
        if(ntid2 !=0) {
            printf("Father ntid2\n");
            pthread_join(ntid2,NULL);
        }

        close(fd_Write[1]);   
        close(fd_Read[0]);    
        exit(0);
    }else{   //Children
        close(fd_Write[1]);   
        close(fd_Read[0]);   
        ppid = getppid();
        //父进程退出后，通知子进程退出，但Kill -9 啥子父进程后子进程依然存活
        prctl(PR_GET_PDEATHSIG , SIGHUP);

        system("pwd");
        sprintf(Str1,"%d",fd_Write[0]);
        sprintf(Str2,"%d",fd_Read[1]);
        execl("usart",argv[1],Str1,Str2,NULL);
        close(fd_Write[0]);  
        close(fd_Read[1]);
        exit(0);
    }
    return 0;
}
