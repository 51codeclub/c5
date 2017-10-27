
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月27日 星期五 15时22分22秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<stdlib.h>

int main()
{
    key_t key = ftok("mytest", 0xff);
    if(key == -1)
    {
        perror("fotk");
        exit(1);
    }
    else 
    {
        printf("key = %x\n",key);
    }


    key = ftok("youtest", 0xff);
    if(key == -1)
    {
        perror("ftok1");
        exit(1);
    }
    else
        printf("key = %x\n",key);

    key = ftok("mytest", 0xfe);
    if(key == -1)
    {
        perror("ftok2");
        exit(1);
    }
    else
        printf("key = %x\n",key);

    key = ftok("mytest",0xff);
    printf("key = %x\n",key);

    return 0;
}
