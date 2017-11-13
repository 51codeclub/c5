
/**********************************************************
*    > File Name: cli.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月13日 星期一 18时56分23秒
**********************************************************/

#include"../utili.h"

int main()
{
    int sockCli = socket(AF_INET, SOCK_STREAM, 0);
    if(sockCli == -1)
    {
        perror("socket.");
        return -1;
    }
    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(SERVER_PORT);
    addrSer.sin_addr.s_addr = inet_addr(SERVER_IP);

    struct sockaddr_in addrCli;
    addrCli.sin_family = AF_INET;
    //addrCli.sin_port = htons(9090);
    addrCli.sin_addr.s_addr = inet_addr("192.168.1.50");
    socklen_t len = sizeof(struct sockaddr);
    int ret = bind(sockCli, (struct sockaddr*)&addrCli, len);
    if(ret == -1)
    {
        perror("bind.");
        return -1;
    }
    ret = connect(sockCli, (struct sockaddr*)&addrSer, len);
    if(ret == -1)
    {
        printf("Client Connect Server Error.\n");
        return -1;
    }
    else
        printf("Client Connect Servetr Success.\n");

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
    while(1)
    {
        recv(sockCli, recvbuf, BUFFER_SIZE, 0);
        printf("Ser:>%s\n",recvbuf);
        printf("Cli:>");
        scanf("%s",sendbuf);
        if(!strcmp(sendbuf,"quit"))
            break;
        send(sockCli, sendbuf, strlen(sendbuf)+1, 0);
    }
    close(sockCli);
    return 0;
}
