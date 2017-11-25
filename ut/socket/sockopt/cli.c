
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月24日 星期五 16时33分48秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

int main()
{
    int sockCli = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(8080);
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");

    int yes = 1;
    //setsockopt(sockSer, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    socklen_t len = sizeof(struct sockaddr);

    connect(sockCli, (struct sockaddr*)&addrSer, len);

    char buffer[128];
    while(1)
    {
        printf("Cli:>");
        scanf("%s",buffer);
        //recv(sockConn, buffer, 128, 0);
        //printf("buffer = %s\n",buffer);
    }


    close(sockCli);
    return 0;
}
