
/**********************************************************
 *    > File Name: ser.c
 *    > Author: 51CC_baosongshan
 *    > Mail: baosongshan2006@163.com 
 *    > Created Time: 2017年11月18日 星期六 09时43分19秒
 **********************************************************/

#include"../calc.h"
#include"../../socket.h"

typedef enum {IDLE, BUSY}WORK_STATE;

#define MAX_THREAD_NUM 5
typedef struct thread_st
{
    int sockConn;
    WORK_STATE flag;     // 0:Idle  1:Busy
}thread_st;

thread_st thread_pool[MAX_THREAD_NUM];


void* thread_handler(void *arg);
int main(int argc, char *argv[])
{
    int sockSer = start_up(argv[1], atoi(argv[2]), TCP);
    printf("Server Wait Client Connect.........\n");

    //
    int i=0;
    pthread_t tid[MAX_THREAD_NUM];
    for(; i<MAX_THREAD_NUM; ++i)
    {
        pthread_create(&tid[i], NULL, thread_handler, &i);
        thread_pool[i].sockConn = 0;
        thread_pool[i].flag = 0;
        sleep(1);
    }

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
            printf("<==========Client==============>\n");
            printf("< ip = %s\n", inet_ntoa(addrCli.sin_addr));
            printf("< port = %d\n",ntohs(addrCli.sin_port));
            printf("<==============================>\n");
        }

        for(i=0; i<MAX_THREAD_NUM; ++i)
        {
            if(thread_pool[i].flag == IDLE)
            {
                thread_pool[i].flag = BUSY;
                thread_pool[i].sockConn = sockConn;
                break;
            }
        }
        if(i == MAX_THREAD_NUM)
        {
            printf("Server Over Load.\n");
        }
    }

    close(sockSer);
    return 0;
}

void* thread_handler(void *arg)
{
    int index = *(int*)arg;
    printf("[%d] thread start up.\n",index);

    int ret_byte_size;
    int result;
    calcst oper;
    while(1)
    {
        if(thread_pool[index].flag == BUSY)
        {
            printf("[%d] thread start work.....\n",index);
            ret_byte_size = recv(thread_pool[index].sockConn, &oper, sizeof(oper), 0);
            if(ret_byte_size < 0)
            {
                perror("redv data error.");
                //continue;
                break;
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

            ret_byte_size = send(thread_pool[index].sockConn, &result, sizeof(result), 0);
            if(ret_byte_size < 0)
            {
                perror("send data error.");
                continue;
            }
        }
        else
        {
            printf("[%d] thread is sleep.....\n",index);
            sleep(1);
        }
    }
    close(thread_pool[index].sockConn);
}










