#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h> 
#include <sys/mman.h>
#define AUDIO_REG_BASE   (0x20C4000)
#define AUDIO_REG_BASE2   (0x20C8000)
#define MAP_SIZE        0xFF
 
static int dev_fd;
int main(int argc, char **argv)
{
 
	dev_fd = open("/dev/mem", O_RDWR | O_NDELAY);      
    printf("argv[1] %s  argv[2] =%s \n ",argv[1],argv[2]);
    int addr = strtol(argv[1],NULL,16);
    int reg = strtol(argv[2],NULL,16);
	//printf("%x \n",argv[1]);
	//printf("addr= %08X,Len =%08X \n",addr,reg);

	if (dev_fd < 0)  
	{
		printf("open(/dev/mem) failed.");    
		return 0;
	}  
 
	unsigned char *map_base=(unsigned char * )mmap(NULL, 0x200, PROT_READ | PROT_WRITE, MAP_SHARED, dev_fd, addr );
 
	printf("0X%08X : 0X%08x \n", (addr + reg),*(volatile unsigned int *)(map_base + reg)); //打印该寄存器地址的value
 
#if 0// LINE IN
	printf("%x \n", *(volatile unsigned int *)(map_base+0x30));
 
	*(volatile unsigned int *)(map_base + 0x30) = 0x208121bc; //修改该寄存器地址的value
	usleep(1000000);
	*(volatile unsigned int *)(map_base + 0x30) &= ~(0x1<<16); //修改该寄存器地址的value
	usleep(1000000);
 
	printf("%x \n", *(volatile unsigned int *)(map_base+0x30));
#endif
 
	if(dev_fd)
		close(dev_fd);
 
	munmap(map_base,MAP_SIZE);//解除映射关系
 
	return 0;
}
