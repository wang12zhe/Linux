/*************************************************************************
	> File Name: test.c
	> Author: lizhu
	> Mail: 1489306911@qq.com
	> Created Time: 2015年11月28日 星期六 11时05分05秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#define DEVTYPE_DISK 2
#define DEVTYPE_U    3
//外部设备的子结构
typedef struct tagDevParam_T
{
    unsigned char  devname[12];
    unsigned char  devtype;///2----硬盘，3----U盘
    unsigned char  partition_count;
    unsigned int dev_totalspace;//KB
    unsigned int partition_size[12];/*分区大小，单位KB*/
} tagDevParam_t, *ptagDevParam_t;

typedef struct tagDevinfo_T
{
    tagDevParam_t dev[8];
    int     devcount; /*总共的设备数量*/
    int     disk_num;
} tagDevinfo_t, *ptagDevinfo_t;


int DvrCpFile(char *srcFile, char *targetFile, int findString, char *string)
    {
        int ret = 0;
        FILE *srcfp = NULL;
        FILE *targetfp = NULL;
        int length = 0;
        ssize_t size;
        size_t len = 0;
        char *p = NULL;
        char *line = NULL;

        if(access(srcFile, F_OK) != 0)
        {
            printf("ERROR: src file is not exist!");
            return -1;
        }
        if(ret == 0)
        {
            srcfp = fopen(srcFile, "r");
            targetfp = fopen(targetFile, "w+");
            if((targetfp != NULL) && (srcfp != NULL))
            {
                while((size = getline(&line, &len, srcfp)) != -1)
                {
                    if(size > 0)
                    {
                        if(findString == 1)
                        {
                            p = strstr(line, string);
                            if(p != NULL)
                            {
                                length = fwrite(line, size, 1, targetfp);
                            }
                        }
                        else
                        {
                            length = fwrite(line, size, 1, targetfp);
                        }
                    }
                }
                fclose(srcfp);
                fclose(targetfp);
                if(line)
                {
                    free(line);
                }
                ret = 0;
            }
            else
            {
                if(srcfp)
                {
                    printf("ERROR: open flie %s", targetFile);
                    fclose(srcfp);
                }
                if(targetfp)
                {
                    printf("ERROR: open flie %s", srcFile);
                    fclose(targetfp);
                }
                ret = -1;
            }
        }
        return ret;
}

int CheckIsDiskOrUsbDisk(unsigned char *devname)
{
    FILE *fp;
    int  ret = -1;
    char buffer[80], * line = NULL;
    ssize_t size;
    size_t len = 0;
    int fal=0;

    memset(buffer, 0, 80);
    char tmpfilename[64];
    if(tmpnam(tmpfilename) == NULL)
    {
        sprintf(tmpfilename, "%s", "/tmp/check_dev_type.txt");
    }
    fp = fopen(tmpfilename, "w+");
    sprintf(buffer, "/sys/block/%s/removable", devname);
    DvrCpFile(buffer, tmpfilename, fal, NULL);
    size = getline(&line, &len, fp);
    fclose(fp);
    ret = atoi(line);
    switch(ret)
    {
        case 0:
            ret = DEVTYPE_DISK;
            break;
        case 1:
            ret = DEVTYPE_U;
            break;
        default:
            ret = -1;
            break;
    }
    if(line)
    {
        free(line);
    }
    remove(tmpfilename);
    return ret;
}
int main(){

    int           xx=1,i=0,dev_tpye;
    ssize_t       size;
    size_t        len = 0;
    unsigned char k;
    tagDevinfo_t  devinfo;
    char          tmp_devname[12];
    char          *line = NULL;
    char          *pname;
    char          *token;
    char          seps[] = " ";
    FILE          *fp = NULL;

    bzero(tmp_devname, 12);
    bzero(&devinfo, sizeof(devinfo));
    DvrCpFile("/proc/partitions", "/tmp/partitions.txt", xx, "sd");
    
    fp = fopen("/tmp/partitions.txt", "r");
    /*获得系统 硬盘 和移动设备总结构*/
    while((size = getline(&line, &len, fp)) != -1)
    {
        pname = strrchr(line, ' ');
        if(pname == NULL)
            continue;
        pname++;
        if(memcmp(pname, tmp_devname, 3) == 0) //新分区
        {
            i = 0;
            token = strtok(line, seps);
            while(token != NULL)
            {
                if(i == 2)
                {
                    k=devinfo.dev[devinfo.devcount-1].partition_count;
                    devinfo.dev[devinfo.devcount-1].partition_size[k]=atoi(token);
                }
                i++;
                token = strtok(NULL, seps);
            }
            devinfo.dev[devinfo.devcount-1].partition_count++;
        }
        else//新设备
        {
            memcpy(devinfo.dev[devinfo.devcount].devname, pname, 3);
            i = 0;
            token = strtok(line, seps);
            while(token != NULL)
            {
                if(i == 2)
                {
                    devinfo.dev[devinfo.devcount].dev_totalspace = atoi(token); 
                }
                i++;
                token = strtok(NULL, seps);
            }
            devinfo.devcount++;
        }
        memcpy(tmp_devname, pname, 3);
    }
    
	printf("dve count =%d\n",devinfo.devcount);
	for(i = 0; i < devinfo.devcount; i++){
			printf("dev name=%s\n",devinfo.dev[i].devname);
			
				dev_tpye = CheckIsDiskOrUsbDisk(devinfo.dev[i].devname);
				devinfo.dev[i].devtype = dev_tpye;
				if(devinfo.dev[i].devtype == DEVTYPE_U)
				{
					printf("this is USB drive");
				}
				if(devinfo.dev[i].devtype == DEVTYPE_DISK)
				{
					printf("this is  hard drive");
				}
			
	}

    return 0;
}


