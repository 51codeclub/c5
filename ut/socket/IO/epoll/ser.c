
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
#include<sys/epoll.h>
#include"../../socket.h"

// ./ser ip port 

#define MAX_CLIENT_SIZE 5

void add_event(int epfd, int fd, int event)
{
    struct epoll_event ev;
    ev.events = event;
    ev.data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
}
void del_event(int epfd, int fd, event)
{
    struct epoll_event ev;
    ev.events = event;
    ev.data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
}

void mod_event(int epfd, int fd, event)
{
    struct epoll_event ev;
    ev.events = event;
    ev.data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);
}

int main(int argc, char *argv[])
{
    int sockSer = start_up(argv[1], atoi(argv[2]), TCP);

    struct sockaddr_in addrCli;
    socklen_t addrlen = sizeof(struct sockaddr);
    char buffer[128];

    int epoll_fd = epoll_create(MAX_CLIENT_SIZE+1);

    add_event(epoll_fd, sockSer, EPOLLIN);

    struct epoll_event revent[MAX_CLIENT_SIZE];
    int i;
    while(1)
    {
        int ret = epoll_wait(epoll_fd, revent, MAX_CLIENT_SIZE, -1);
        if(ret == 0)
        {
            perror("epoll_wait.");
            continue;
        }
        else if(ret == 0)
        {
            printf("time out.\n");
            continue;
        }
        else
        {
            for(i=0; i<ret; ++i)
            {
                if(revent[i].data.fd==sockSer && (revent[i].events & EPOLLIN))
                {
                    int sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &addrlen);
                    if(sockConn == -1)
                    {
                        perror("accept");
                        continue;
                    }
                    
                    if(i >= MAX_CLIENT_SIZE)
                    {
                        printf("Servet Over Load.\n");
                    }
                    else
                    {
                        add_event(epoll_fd, sockConn, EPOLLIN);

                        printf("A New Client Come Baby......\n");
                    }
                }
                else if(revent[i].data.fd!=0 && (revent[i].events & EPOLLIN))
                {
                     int recvbyte = recv(revent[i].data.fd, buffer, 128, 0);
                    if(recvbyte <= 0)
                    {
                        perror("recv data.");
                        break;
                    }
                    int sendbyte = send(revent[i].data.fd, buffer, strlen(buffer)+1, 0);
                    if(sendbyte <= 0)
                    {
                        perror("send data.");
                        break;
                    }
                }
            }
        }
    }

   close(sockSer);
    return 0;
}





