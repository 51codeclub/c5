
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
    long msg_type;
    char     msg_text[MSG_BUFFER_SIZE];
}Msg;

int main(int argc, char *argv[])
{
    key_t msg_key = Ftok(argv[1], atoi(argv[2]));
    int msg_id = Msgget(msg_key, IPC_CREAT|IPC_EXCL|0755);

    Msg msg;
    memset(&msg, 0, sizeof(msg));
    while(1)
    {
        printf("Ser:>");
        scanf("%s", msg.msg_text);
        msg.msg_type = SER_SND_FLG;
        msgsnd(msg_id, &msg, strlen(msg.msg_text)+1, 0);

        memset(&msg, 0, sizeof(msg));
        msgrcv(msg_id, &msg, MSG_BUFFER_SIZE,  SER_RCV_FLG, 0);
        printf("Cli:>%s\n",msg.msg_text);
    }

    msgctl(msg_id, IPC_RMID, NULL);

    return 0;
}
