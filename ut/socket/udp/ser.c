
/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月13日 星期一 20时50分06秒
**********************************************************/

#include"utili.h"

int main()
{
    int sockSer = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockSer == -1)
    {
        perror("socket.");
        return -1;
    }
    struct sockaddr_in addrSer, addrCli;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(9090);
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");

    socklen_t len = sizeof(struct sockaddr);
    int ret = bind(sockSer, (struct sockaddr*)&addrSer, len);
    if(ret == -1)
    {
        perror("bind");
        return -1;
    }

    char sendbuf[128];
    char recvbuf[128];
    while(1)
    {
        recvfrom(sockSer, recvbuf, 128, 0, (struct sockaddr*)&addrCli, &len);
        printf("Cli:>%s\n",recvbuf);
        printf("Ser:>");
        scanf("%s",sendbuf);
        sendto(sockSer, sendbuf, strlen(sendbuf)+1, 0, (struct sockaddr*)&addrCli, len);
    }

    close(sockSer);
    return 0;
}







