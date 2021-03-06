
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

unsigned char ReteyCnt =5;



struct FDStruct{
    int fdwr;
    int fdrd;
};
/* 毫秒级 延时 */
void mssleep(int ms)
{
	struct timeval delay;
	delay.tv_sec = 0;
	delay.tv_usec = ms * 1000; // 20 ms
	select(0, NULL, NULL, NULL, &delay);

}

INT8U SendData(struct Command Cmd){
    INT8U ReteyCnt = 5;
    do{
        Cmd.fp_Action(Cmd.Parameter);
        TM_Delay(DELAY_1S);
        ReteyCnt --;
    }while(ReteyCnt > 0);

    return ReteyCnt;
}



INT8U InitializeSensor(void){
    INT8U i =0;

    for(i =0;i< SensorTableTotal;i ++ ){
        if( 0 !=SendData(SensorTable[i])){
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
   InitializeSensor();
    while(1){
        ShowTime();
        //SendData(SensorTable[SensorTableTotal -1]);
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
                    ReteyCnt=0;
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

    if(argc != 1){  
        printf("=========================\n");  
        printf("Usage: %s   \n",argv[0]);
        printf("=========================\n");
        exit(1);   
    } 
    //为信号设置信号处理函数
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

        PIPE_fd.fdrd = fd_Read[0];
        PIPE_fd.fdwr = fd_Write[1];
 
        err = pthread_create(&ntid1, NULL, (void *)ReadData, (&PIPE_fd.fdrd));
        if (err != 0){
            perror("can't create thread");     
        } 
        err = pthread_create(&ntid2, NULL, (void *)ParserCommand, (&PIPE_fd));
        if (err != 0){
            perror("can't create thread");     
        } 
        
        if(ntid1 !=0) {
            printf("ntid1\n");
            pthread_join(ntid1,NULL);
        }
        if(ntid2 !=0) {
            printf("ntid1\n");
            pthread_join(ntid2,NULL);
        }

        close(fd_Write[1]);   
        close(fd_Read[0]);    
        exit(0);
    }else{   //Children
        close(fd_Write[1]);   
        close(fd_Read[0]);   
        ppid = getppid();

        prctl(PR_GET_PDEATHSIG , SIGHUP);

        system("pwd");
        sprintf(Str1,"%d",fd_Write[0]);
        sprintf(Str2,"%d",fd_Read[1]);
        execl("bin/usart","/dev/ttyUSB0",Str1,Str2,NULL);

        close(fd_Write[0]);  
        close(fd_Read[1]);
        exit(0);
    }
    return 0;
}
