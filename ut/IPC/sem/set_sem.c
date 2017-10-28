
/**********************************************************
*    > File Name: set_sem.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月28日 星期六 09时52分35秒
**********************************************************/

#include"../ipc.h"

// ./set_sem mysem 0xff 5

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        printf("<Warning:Usage>: %s pathname proj_id sem_val.\n",argv[0]);
        return -1;
    }
    key_t sem_key = Ftok(argv[1],atoi(argv[2]));
    int sem_id = Semget(sem_key, 0, 0);

    union semun init;
    init.val = atoi(argv[3]);
    int ret = semctl(sem_id, 0, SETVAL, init);
    if(ret == -1)
        printf("set sem Error.\n");
    else
        printf("set sem Success.\n");

    return 0;
}
    
