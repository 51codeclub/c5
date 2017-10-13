
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月13日 星期五 14时49分24秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>

//  ./test  pathname

int main(int argc, char *argv[])
{
    struct stat info;
    stat(argv[1], &info);

    if(S_ISDIR(info.st_mode))
        printf("%s is Dir.\n",argv[1]);
    else
        printf("%s is not Dir\n",argv[1]);

    return 0;
}
