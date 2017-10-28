
/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月28日 星期六 10时57分22秒
**********************************************************/

#include"../ipc.h"
#include<sys/shm.h>

int main()
{
    key_t shm_key = Ftok("myshm", 0xff);
    int shm_id = Shmget(shm_key, 0, 0);
    char *addr = (char *)Shmat(shm_id, NULL, 0);

    ////////////////////////////////////////////////////////////
    int sem_id = Semget(shm_key, 0, 0);

    struct sembuf v = {1, 1, 0};
    struct sembuf p = {0, -1,0};
    ////////////////////////////////////////////////////////////

    while(1)
    {
        semop(sem_id, &p, 1);
        printf("Ser:> %s\n",addr);

        printf("Cli:>");
        scanf("%s",addr);
        semop(sem_id, &v, 1);

    }

    shmdt(addr);
    return 0;
}

