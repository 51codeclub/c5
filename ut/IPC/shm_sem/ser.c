
/**********************************************************
*    > File Name: ser.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月30日 星期一 18时57分40秒
**********************************************************/

#include"../ipc.h"

// ./ser myshm 0xff
int main(int argc, char *argv[])
{
    key_t shm_key = Ftok(argv[1], atoi(argv[2]));
    int shm_id = Shmget(shm_key, 1024, IPC_CREAT|IPC_EXCL|0755);

    char *addr = (char*)Shmat(shm_id, NULL, 0);
    

    int sem_id = Semget(shm_key, 2, IPC_CREAT|IPC_EXCL|0755);
    union semun init;
    init.val = 0;

    semctl(sem_id, 0, SETVAL, init);
    semctl(sem_id, 1, SETVAL, init);

    struct sembuf v = {0, 1, 0};
    struct sembuf p = {1, -1, 0};    

    while(1)
    {
        printf("Ser:>");
        scanf("%s",addr);
        semop(sem_id, &v, 1);

        semop(sem_id, &p, 1);
        printf("Cli:>%s\n",addr);
    }

    semctl(sem_id, 0, IPC_RMID);
    semctl(sem_id, 1, IPC_RMID);
    shmdt(addr);
    
    shmctl(shm_id, IPC_RMID, NULL);
    return 0;
}
