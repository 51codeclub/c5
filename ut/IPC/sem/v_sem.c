
/**********************************************************
*    > File Name: set_sem.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月28日 星期六 09时52分35秒
**********************************************************/

#include"../ipc.h"

// ./p_sem mysem 0xff 5

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("<Warning:Usage>: %s pathname proj_id.\n",argv[0]);
        return -1;
    }
    key_t sem_key = Ftok(argv[1],atoi(argv[2]));
    int sem_id = Semget(sem_key, 0, 0);

    struct sembuf info;
    info.sem_num = 0;
    info.sem_op = 1;
    info.sem_flg = 0;

    int ret = semop(sem_id, &info, 1);
    if(ret == -1)
        printf("operator sem Error.\n");
    else
        printf("operator sem Success.\n");

    return 0;

}
    
