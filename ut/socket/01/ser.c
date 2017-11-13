/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月11日 星期六 10时22分00秒
**********************************************************/

#include"../socket.h"

// ./ser 192.168.1.50 8080

int main(int argc, char *argv[])
{
    int sockSer = start_up(argv[1], atoi(argv[2]), TCP);
    if(sockSer == -1)
    {
        return -1;
    }
    int sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &len);
    if(sockConn == -1)
    {
        printf("Server Accept Client Connect Fail.\n");
        exit(1);
    }
    else
    {
        printf("Server Accept Client Connect Success.\n");
    }

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
    while(1)
    {
        printf("Ser:>");
        scanf("%s", sendbuf);
        send(sockConn, sendbuf, strlen(sendbuf)+1, 0);
        recv(sockConn, recvbuf, BUFFER_SIZE, 0);
        printf("Cli:>%s\n",recvbuf);
    }

    close(sockSer);

    return 0;
}









