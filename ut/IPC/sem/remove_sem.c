
/**********************************************************
*    > File Name: remove_sem.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月28日 星期六 09时28分51秒
**********************************************************/

#include"../ipc.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("<Waring:Usage>: %s parhname proj_id.\n", argv[0]);
        return -1;
    }
    key_t sem_key = Ftok(argv[1], atoi(argv[2]));
    int sem_id = Semget(sem_key, 0, 0);

    int ret = semctl(sem_id, 0, IPC_RMID);
    if(ret == -1)
        printf("remove sem Error.\n");
    else
        printf("remove sem Success.\n");

    return 0;
}
