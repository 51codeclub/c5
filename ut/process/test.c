
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月16日 星期一 19时09分25秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* thread_fun(void *arg)
{
    int i;
    for(i=0; i<10; ++i)
    {
        printf("This is Child Thread.\n");
    }
    return NULL;
}

int main()
{
    int i;
    pthread_t tid;
    pthread_create(&tid, NULL, thread_fun, NULL);
    
    for(i=0; i<10; ++i)
    {
        printf("This is Main Thread.\n");
    }
    return 0;
}

/*
int main()
{
    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
        printf("Child Sleep......\n");
        sleep(5);
        printf("This is Child.\n");
    }
    else if(pid > 0)
    {
        printf("Parent Wait.....\n");
        //sleep(4);
        int status;
        wait(&status);
        printf("This is Parent.\n");
    }
    else
    {
        perror("fork");
    }
    return 0;
}

/*
int main()
{
    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
        printf("child ppid = %d\n",getppid());
        sleep(2);
        printf("Child.\n");
        printf("child ppid = %d\n",getppid());
    }
    else if(pid > 0)
    {
        printf("parent pid = %d\n",getpid());
        sleep(1);
        printf("Parent.\n");
    }
    else
    {
        perror("fork");
    }
    return 0;
}

/*
int main()
{
    pid_t pid;
    pid = fork();
    pid = fork();
    if(pid > 0)
    {
        printf("Parent.ppid[%d]\n",getpid());
    }
    else if(pid == 0)
    {
        printf("Child.pid[%d]\n",getpid());
        printf("My Parent pid[%d]\n",getppid());
    }
    else
    {
        perror("fork.");
    }

    sleep(30);
    return 0;
}

/*
int main()
{
    pid_t pid;
    pid = fork();
    
    switch(pid)
    {
    case -1:
        perror("fork");
        break;
    case 0:
        printf("This is child process.pid = %d\n",getpid());
        break;
    default:
        printf("This is parent process,pid = %d\n",getpid());
        break;
    }
    return 0;
}

/*
int fun()
{
    printf("in fun: pid = %d\n",getpid());
}

int main()
{
    printf("pid = %d\n",getpid());
    printf("ppid = %d\n",getppid());
    fun();
    sleep(10);
    return 0;
}

/*
int main()
{
    int i = 0;
    for(;i<100; ++i)
    {
        printf("i = %d\n",i);
        sleep(1);
    }
    return 0;
}
*/
