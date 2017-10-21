
/**********************************************************
*    > File Name: test.c

 *    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月20日 星期五 14时14分32秒
**********************************************************/
#include<stdio.h>
#include<unistd.h>
#include<wait.h>
#include<stdlib.h>
#include<sys/resource.h>

//myls

int main()
{
    //execl("/bin/ls","ls",NULL);
    printf("test pid = %d\n",getpid());
    pid_t pid = fork();
    if(pid == 0)
    {
        printf("I Go tt.....\n");
        printf("child pid = %d, ppid = %d\n",getpid(), getppid());
        execl("tt","tt", NULL);
        printf("====================\n");
    }
    else if(pid > 0)
    {
        int status;
        wait(&status);
    }
    return 0;
}

/*
int main()
{
    pid_t pid = fork();
    int pri;
    if(pid == 0)
    {
        pri = getpriority(PRIO_PROCESS, getpid());
        printf("child pri = %d\n",pri);
        nice(2);
        pri = getpriority(PRIO_PROCESS, getpid());
        printf("child pri = %d\n",pri);
        nice(3);
        pri = getpriority(PRIO_PROCESS, getpid());
        printf("child pri = %d\n",pri);
    }
    else if(pid > 0)
    {
        pri = getpriority(PRIO_PROCESS, getpid());
        printf("parent pri = %d\n",pri);
    }
    return 0;
}

/*
int main()
{
    int i = 0;
    for(; i<2; ++i)
    {
        vfork();
    }
    printf("pid = %d\n",getpid());

    exit(0);
}


/*
int main()
{
    int i = 0;
    pid_t pid = vfork();
    if(pid == 0)
    {
        i = 10;
        printf("in child i = %d\n",i);
        exit(0);
    }
    else if(pid > 0)
    {
        printf("in parent i = %d\n", i);
        int status;
        wait(&status);
    }
    return 0;
}

/*
int g_p = 0;

int main()
{
    pid_t pid;
    pid_t g_pid;
    pid = fork();

    if(pid == 0)
    {
        pid = fork();
        if(pid == 0)
        {
            g_p = getpid();
            printf("3 pid = %d\n",getpid());
        }
        else if(pid > 0)
        {
            printf("1 pid = %d\n",getpid());
            sleep(3);
        }
    }
    else if(pid > 0)
    {
        g_pid = pid;
        pid = fork();
        if(pid == 0)
        {
            printf("2 pid = %d\n",getpid());
            sleep(1);
        }
        else if(pid > 0)
        {
            printf("0 pid = %d\n",getpid());
            int status;
            //pid = wait(&status);
            printf("g_p = %d\n",g_p);
            pid = waitpid(g_p, &status, WUNTRACED);
            
            printf("wait process id = %d\n",pid);
        }
    }
    else
    {
        perror("fork.");
    }

    printf("%d process finish.\n",getpid());

    return 0;
}

/*
int main()
{
    pid_t pid;
    pid = fork();

    if(pid == 0)
    {
        printf("child pid = %d\n",getpid());
        sleep(5);
    }
    else if(pid > 0)
    {
        printf("parent pid = %d\n",getpid());
        sleep(1);
        kill(pid, SIGINT);
        int status;
        pid_t pid_ret = wait(&status);
        printf("pid_ret = %d\n",pid_ret);

        if(WIFEXITED(status))
        {
            printf("child process is OK finish.\n");
        }
        else
        {
            printf("child process is Error finish.\n");
        }
    }
    else
    {
        perror("fork.");
    }

    printf("%d finish.\n",getpid());

    return 0;
}
*/
