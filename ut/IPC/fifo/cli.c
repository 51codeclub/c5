
/**********************************************************
*    > File Name: cli.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月21日 星期六 11时12分16秒
**********************************************************/

#include"utili.h"

int main()
{
    int read_fd = open(write_fifo, O_RDONLY);
    if(read_fd == -1)
    {
        perror("open write_fd");
        exit(1);
    }

    int ret = mkfifo(read_fifo, O_CREAT|O_EXCL|0755);
    if(ret == -1)
    {
        perror("mkfifo");
        close(read_fd);
        exit(1);
    }
    int write_fd = open(read_fifo, O_WRONLY);
    if(write_fd == -1)
    {
        perror("open read_fifo");
        close(read_fd);
        exit(1);
    }

    char send_buf[256];
    char recv_buf[256];
    while(1)
    {
        read(read_fd, recv_buf, 256);
        printf("Ser:>%s\n",recv_buf);
        printf("Cli:>");
        scanf("%s",send_buf);
        write(write_fd, send_buf, strlen(send_buf)+1);
    }

    close(write_fd);
    close(read_fd);


    return 0;
}








