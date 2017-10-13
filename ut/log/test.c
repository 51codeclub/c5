
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月09日 星期一 19时25分28秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<syslog.h>
#include<errno.h>
#include<fcntl.h>
int main()
{
    int fd = open("a.txt", O_WRONLY|O_CREAT, 0755);

    close(1);
    dup(fd);

    printf("Hello Liuna.\n");
    return 0;
}

/*
//printf

int main()
{
    FILE *fp = fopen("test.txt","r");
    if(fp == NULL)
    {
        openlog("51cc_c5",LOG_PID|LOG_CONS, LOG_USER);
        syslog(LOG_DEBUG, "%m\n");
        closelog();
        return -1;
    }
    fclose(fp);
    return 0;
}

/*
int main()
{
    FILE *fp = fopen("test.txt", "r");
    if(fp == NULL)
    {
        //syslog(LOG_INFO,"%s\n","open test.txt file fail.");
        syslog(LOG_INFO,"%m\n");
        return -1;
    }
    fclose(fp);
    return 0;
}
*/
