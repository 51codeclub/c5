
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

#include<sys/select.h>

#include"../../socket.h"

// ./ser ip port 

#define MAX_CLIENT_SIZE 5

int main(int argc, char *argv[])
{
    int sockSer = start_up(argv[1], atoi(argv[2]), TCP);

    int client_sockConn[MAX_CLIENT_SIZE] = {0};
    int client_conn_num = 0; //

    struct sockaddr_in addrCli;
    socklen_t addrlen = sizeof(struct sockaddr);
    char buffer[128];

    fd_set set;
    int maxfd = sockSer;
    int i;
    while(1)
    {
        FD_ZERO(&set);
        FD_SET(sockSer, &set);

        for(i=0; i<MAX_CLIENT_SIZE; ++i)
        {
            if(client_sockConn[i] != 0)
            {
                FD_SET(client_sockConn[i], &set);
            }
        }

        printf("Server Wait.......\n");
        int ret = select(maxfd+1, &set, NULL, NULL, NULL);
        if(ret == -1)
        {
            perror("select.");
            continue;
        }
        else if(ret == 0)
        {
            printf("time out.\n");
            continue;
        }
        else
        {
            if(FD_ISSET(sockSer, &set))
            {
                //new client
                int sockConn = accept(sockSer, (struct sockaddr *)&addrCli, &addrlen);
                if(sockConn == -1)
                {
                    printf("Server Accept Client Connect Fail.\n");
                    continue;
                }
                else
                {
                    printf("A New Client Come Baby.\n");
                    client_conn_num++;
                    for(i=0; i<MAX_CLIENT_SIZE; ++i)
                    {
                        if(client_sockConn[i] == 0)
                        {
                            client_sockConn[i] = sockConn;
                            break;
                        }
                    }
                    if(i >= MAX_CLIENT_SIZE)
                    {
                        printf("Server Over Load.\n");
                    }
                    else
                    {
                        if(sockConn > maxfd)
                            maxfd = sockConn;
                    }
                }
            }
            else
            {
                printf("Server Handler Client Msg.\n");
                for(i=0; i<MAX_CLIENT_SIZE; ++i)
                {
                    if(FD_ISSET(client_sockConn[i], &set))
                    {
                        //handler client msg
                        int recvbyte = recv(client_sockConn[i], buffer, 128, 0);
                        if(recvbyte <= 0)
                        {
                            printf("Recv DataError.\n");
                            continue;
                        }
                        send(client_sockConn[i], buffer, strlen(buffer)+1, 0);
                    }
                }
            }
        }
    }

    close(sockSer);
    return 0;
}





