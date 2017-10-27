
/**********************************************************
 *    > File Name: cli.c
 *    > Author: 51CC_baosongshan
 *    > Mail: baosongshan2006@163.com 
 *    > Created Time: 2017年10月21日 星期六 11时12分16秒
 **********************************************************/

#include"utili.h"

void write_msg(int fd)
{
    char buf[256];
    while(1)
    {
        printf("Cli:>");
        scanf("%s",buf);
        if(!strcmp(buf,"quit"))
        {
            break;
        }
        write(fd, buf, strlen(buf)+1);
    }
}
void read_msg(int fd)
{
    int buf[256];
    while(1)
    {
        read(fd, buf, 256);
        printf("Ser:>%s\n",buf);
    }
}

int main()
{
    int read_fd = open(write_fifo, O_RDONLY);
    if(read_fd == -1)
    {
        perror("open write_fd");
        exit(1);
    }

    int ret;
    if((ret=access(read_fifo, F_OK))!= 0)
    {
        ret = mkfifo(read_fifo, O_CREAT|0755);
        if(ret == -1)
        {
            perror("mkfifo");
            close(read_fd);
            exit(1);
        }
    }
    int write_fd = open(read_fifo, O_WRONLY);
    if(write_fd == -1)
    {
        perror("open read_fifo");
        close(read_fd);
        exit(1);
    }

    pid_t pid = fork();
    if(pid == 0)
    {
        write_msg(write_fd);
    }
    else if(pid > 0)
    {
        pid = fork();
        if(pid == 0)
        {
            read_msg(read_fd);
        }
        else if(pid > 0)
        {
            int status;
            wait(&status);
            close(write_fd);
            close(read_fd);
        }
    }




    return 0;
}








