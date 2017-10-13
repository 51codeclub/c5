
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月09日 星期一 21时42分03秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include"log.h"

int main()
{
    set_loglevel(LOG_DEBUG);
    sys_log(LOG_INFO, __FILE__, __LINE__, "Test log Level.\n");
    //sys_log(LOG_INFO, "Test log level.%s\n","hjlfalla");
    FILE *fp = fopen("test.txt","r");
    if(fp == NULL)
    {
        sys_log(LOG_ERR, __FILE__, __LINE__, "open %s file fail.","test.txt");
        return -1;
    }
    fclose(fp);
    return 0;
}
