
/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月18日 星期六 09时43分19秒
**********************************************************/

#include<iostream>
#include"../calc.h"
#include"../../socket.h"
#include<stdlib.h>
#include<string.h>
#include<list>
using namespace std;

typedef struct client_node
{
    char ip[16];
    short port;
}client_node;

typedef struct client_info
{
    int client_num;
    list<client_node*> lt;
}client_info;

void process_handler(int sockConn);

void* Server_Seach(void *arg)
{
    client_info *info = (client_info*)arg;
    int select = 1;
    while(select)
    {
        printf("***********************************\n");
        printf("* [1] Search Client Num           *\n");
        printf("* [2] Search Client Info          *\n");
        printf("* [0] Quit System                 *\n");
        printf("***********************************\n");
        printf("Input Choice:>");
        scanf("%d",&select);
        switch(select)
        {
        case 1:
            printf("client number:> %d\n",info->client_num);
            break;
        case 2:
            {
                list<client_node *>::iterator it = (info->lt).begin();
                while(it != (info->lt).end())
                {
                    cout<<"----------------------"<<endl;
                    cout<<"* client ip:>"<<(*it)->ip<<endl;
                    cout<<"* client port:>"<<(*it)->port<<endl;
                    cout<<"----------------------"<<endl;
                    ++it;
                }
            }
            break;
        }
    }
}


int main(int argc, char *argv[])
{
    client_info client;
    client.client_num = 0;

    pthread_t tid;
    pthread_create(&tid, NULL, Server_Seach, &client);

    int sockSer = start_up(argv[1], atoi(argv[2]), TCP);
    //printf("Server Wait Client Connect.........\n");

    calcst oper;
    struct sockaddr_in addrCli;
    socklen_t len = sizeof(struct sockaddr);
    int sockConn;
    while(1)
    {
        sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &len);
        if(sockConn == -1)
        {
            perror("Accept Client Connect Error.");
            continue;
        }
        else
        {
            client.client_num++;
            client_node *s = (client_node*)malloc(sizeof(client_node));
            strcpy(s->ip, inet_ntoa(addrCli.sin_addr));
            s->port = ntohs(addrCli.sin_port);
            client.lt.push_back(s);
        }

        pid_t pid = fork();
        if(pid == 0)
        {
            process_handler(sockConn);
        }
        else if(pid > 0)
        {
            //int status;
            //wait(&status);
            close(sockConn);
        }
        else
        {
            perror("fork process.");
        }
    }

    close(sockSer);
    return 0;
}

void process_handler(int sockConn)
{
    int ret_byte_size;
    int result;
    calcst oper;
    while(1)
    {
        ret_byte_size = recv(sockConn, &oper, sizeof(oper), 0);
        if(ret_byte_size < 0)
        {
            perror("redv data error.");
            continue;
        }
        if(oper.op == ADD)
            result = oper.op1 + oper.op2;
        else if(oper.op == SUB)
            result = oper.op1 - oper.op2;
        else if(oper.op == MUL)
            result = oper.op1 * oper.op2;
        else if(oper.op == DIV)
            result = oper.op1 / oper.op2;
        else if(oper.op == MOD)
            result = oper.op1 % oper.op2;
        else if(oper.op == QUIT)
        {
            printf("Client Quit.\n");
            break;
        }
        
        ret_byte_size = send(sockConn, &result, sizeof(result), 0);
        if(ret_byte_size < 0)
        {
            perror("send data error.");
            continue;
        }
    }
    close(sockConn);
}










