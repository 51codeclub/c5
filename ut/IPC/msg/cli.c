
/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月30日 星期一 20时27分11秒
**********************************************************/

#include"../ipc.h"
#include"utili.h"
typedef struct Msg
{
    long  msg_type;
    char     msg_text[MSG_BUFFER_SIZE];
}Msg;

int main(int argc, char *argv[])
{
    key_t msg_key = Ftok(argv[1], atoi(argv[2]));
    int msg_id = Msgget(msg_key, 0);

    Msg msg;
    memset(&msg, 0, sizeof(msg));
    char recvbuf[MSG_BUFFER_SIZE];
    while(1)
    {
        msgrcv(msg_id, &msg, MSG_BUFFER_SIZE, CLI_RCV_FLG, 0);
        printf("Ser:>%s\n",msg.msg_text);

        memset(&msg, 0, sizeof(msg));
        printf("Cli:>");
        scanf("%s", msg.msg_text);
        msg.msg_type = CLI_SND_FLG;
        msgsnd(msg_id, &msg, strlen(msg.msg_text)+1, 0);
    }

    return 0;
}
