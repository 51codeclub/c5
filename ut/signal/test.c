
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年12月02日 星期六 10时42分15秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void signal_handler(int sig)
{
    switch(sig)
    {
    case SIGINT:
        printf("Catch [%d] signal: SIGINT\n",sig);
        break;
    case SIGQUIT:
        printf("Catch [%d] signal: SIGQUIT\n",sig);
        break;
    case SIGALRM:
        printf("Catch [%d] signal: SIGALRM\n",sig);
        break;
    case SIGSTOP:
        printf("Catch [%d] signal: SIGSTOP\n",sig);
        break;
    default:
        printf("sig is error.\n");
        break;

    }

}

int main()
{
    alarm(5);
    signal(SIGINT, signal_handler); // ctrl + c
    signal(SIGQUIT, signal_handler); // strl + '\' 
    signal(SIGSTOP, signal_handler);// strl + z
    signal(SIGALRM, signal_handler);

    while(1)
    {
        sleep(1);
    }
    return 0;
}

/*
int main()
{
    //alarm(5);

    int i = 0;
    while(1)
    {
        printf("i = %d\n",++i);
    }
    return 0;
}

/*
int main()
{
    pid_t pid = fork();
    if(pid == 0)
    {
        printf("Hello Child.\n");
        sleep(5);
        raise(SIGINT);
        printf("child wake up.\n");
    }
    else if(pid > 0)
    {
        printf("Hello Parent.\n");
        sleep(3);
        //kill(pid, SIGINT);
        //raise(SIGINT);

        int status;
        wait(&status);
    }


    return 0;
}

*/
