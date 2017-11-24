
/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月18日 星期六 09时43分19秒
**********************************************************/

#include"../calc.h"
#include"../../socket.h"

void process_handler(int sockConn);

int main(int argc, char *argv[])
{
    int sockSer = start_up(argv[1], atoi(argv[2]), TCP);
    printf("Server Wait Client Connect.........\n");

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










