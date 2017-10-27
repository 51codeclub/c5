
/**********************************************************
 *    > File Name: ser.c
 *    > Author: 51CC_baosongshan
 *    > Mail: baosongshan2006@163.com 
 *    > Created Time: 2017年10月21日 星期六 11时01分43秒
 **********************************************************/

#include"utili.h"

void write_msg(int fd);
void read_msg(int fd);

int main()
{
    int ret;
    if((ret=access(write_fifo, F_OK) != 0))
    {
        ret = mkfifo(write_fifo, O_CREAT|0755);
        if(ret == -1)
        {
            perror("mkfifo.");
            exit(1);
        }
    }
    int write_fd = open(write_fifo, O_WRONLY);
    if(write_fd == -1)
    {
        perror("open write_fd.");
        exit(1);
    }

    int read_fd;
    while( (read_fd = open(read_fifo, O_RDONLY)) == -1)
    {
        printf("Client is not start up.\n");
        sleep(1);
    }

    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
        //write
        write_msg(write_fd);
    }
    else if(pid > 0)
    {
        pid = fork();
        if(pid == 0)
        {
            //read
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
    else
    {
        perror("fork.");
    }

    return 0;
}


void write_msg(int fd)
{
    char buf[256];
    while(1)
    {
        printf("Ser:>");
        scanf("%s",buf);
        if(!strcmp(buf, "quit"))
        {
            break;
        }
        write(fd, buf, strlen(buf)+1);
        memset(buf, 0, 256);
    }
}

void read_msg(int fd)
{
    char buf[256];
    while(1)
    {
        memset(buf, 0, 256);
        read(fd, buf, 256);
        printf("Cli:>%s\n",buf);
    }
}




