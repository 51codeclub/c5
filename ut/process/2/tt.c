
/**********************************************************
*    > File Name: tt.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月20日 星期五 15时45分33秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("tt pid = %d, ppid = %d\n",getpid(),getppid());
    sleep(2);
    printf("tt wake up.\n");
    return 0;
}
