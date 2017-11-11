
/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月11日 星期六 10时22分00秒
**********************************************************/

#include"utili.h"

int main()
{
    int sockSer = socket(AF_INET, SOCK_STREAM, 0);
    if(sockSer == -1)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addrSer, addrCli;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(SERVER_PORT);
    addrSer.sin_addr.s_addr = inet_addr(SERVER_IP);

    socklen_t len = sizeof(struct sockaddr);
    int ret = bind(sockSer, (struct sockaddr*)&addrSer, len);
    if(ret == -1)
    {
        perror("bind");
        exit(1);
    }

    ret = listen(sockSer, LISTEN_QUEUE_SIZE);
    if(ret == -1)
    {
        perror("listen");
        exit(1);
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









