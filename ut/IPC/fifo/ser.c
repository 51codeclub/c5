
/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月21日 星期六 11时01分43秒
**********************************************************/

#include"utili.h"

int main()
{
    int ret = mkfifo(write_fifo, O_CREAT|O_EXCL|0755);
    if(ret == -1)
    {
        perror("mkfifo.");
        exit(1);
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

    char send_buf[256];
    char recv_buf[256];
    while(1)
    {
        printf("Ser:>");
        scanf("%s",send_buf);
        write(write_fd, send_buf, strlen(send_buf)+1);
        read(read_fd, recv_buf, 256);
        printf("Cli:>%s\n",recv_buf);
    }

    close(write_fd);
    close(read_fd);

    return 0;
}







