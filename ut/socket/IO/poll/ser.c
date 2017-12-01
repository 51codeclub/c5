
/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月25日 星期六 09时39分35秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<poll.h>
#include"../../socket.h"

// ./ser ip port 

#define MAX_CLIENT_SIZE 5

int main(int argc, char *argv[])
{
    int sockSer = start_up(argv[1], atoi(argv[2]), TCP);

    struct sockaddr_in addrCli;
    socklen_t addrlen = sizeof(struct sockaddr);
    char buffer[128];

    struct pollfd client_fd[MAX_CLIENT_SIZE+1];
    client_fd[0].fd = sockSer;
    client_fd[0].events = POLLIN;

    int i;
    for(i=1; i<MAX_CLIENT_SIZE; ++i)
        client_fd[i].fd = 0;

    int numfd = 1;

    while(1)
    {
        int ret= poll(client_fd, numfd, 3000);
        if(ret == -1)
        {
            perror("poll.");
            continue;
        }
        else if(ret == 0)
        {
            printf("time out.\n");
            continue;
        }
        else
        {
            if(client_fd[0].revents & POLLIN)
            {
                int sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &addrlen);
                if(sockConn == -1)
                {
                    perror("accept");
                    continue;
                }
                for(i=1; i<MAX_CLIENT_SIZE; ++i)
                {
                    if(client_fd[i].fd == 0)
                    {
                        client_fd[i].fd = sockConn;
                        client_fd[i].events = POLLIN;
                        numfd++;
                        break;
                    }
                }
                if(i >= MAX_CLIENT_SIZE)
                {
                    printf("Servet Over Load.\n");
                }
                else
                {
                    printf("A New Client Come Baby......\n");
                }
            }
            else
            {
                for(i=1; i<MAX_CLIENT_SIZE; ++i)
                {
                    if(client_fd[i].fd!=0 && (client_fd[i].revents & POLLIN))
                    {
                        int recvbyte = recv(client_fd[i].fd, buffer, 128, 0);
                        if(recvbyte <= 0)
                        {
                            perror("recv data.");
                            break;
                        }
                        int sendbyte = send(client_fd[i].fd, buffer, strlen(buffer)+1, 0);
                        if(sendbyte <= 0)
                        {
                            perror("send data.");
                            break;
                        }
                    }
                }
            }

        }
    }

    close(sockSer);
    return 0;
}





