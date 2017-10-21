
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月21日 星期六 09时40分01秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include"../../log.h"
#include<stdlib.h>

int main()
{
    char *parent_talk[] = {"Hello", "Can you tell me current time?","Oh MyGod, i have go.ByeBye",NULL};
    char *child_talk[] = {"Hi","No Problem.","GoodBye.",NULL};



    pid_t pid = fork();
    if(pid == 0)
    {}
    else if(pid > 0)
    {}
    else
    {}

    return 0;
}

/*
int main()
{
    pid_t pid;
    
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1)
    {
        sys_log(LOG_ERR,__FILE__,__LINE__,"Create pipe fail.");
        exit(1);
    }
    else
    {
        sys_log(LOG_INFO, __FILE__, __LINE__, "Create pipe Success.");
    }
    
    pid = fork();

    if(pid == 0)
    {
        close(fd[1]);

        char buffer[256];
        read(fd[0], buffer, 256);
        printf("Form Parent Process msg:> %s\n", buffer);
        close(fd[0]);
    }
    else if(pid > 0)
    {
        char *msg = "GoodGoodStudy, DayDayUp.";
        close(fd[0]);
        write(fd[1], msg, strlen(msg)+1);
        close(fd[1]);

        int status;
        wait(&status);
    }
    else
    {
        perror("fork.");
    }

    return 0;
}
