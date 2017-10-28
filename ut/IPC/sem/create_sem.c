
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月27日 星期五 16时01分04秒
**********************************************************/

#include"../ipc.h"
#include<sys/sem.h>

// ./create_sem mysem 0xff n

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        printf("<Waring:Usage> %s pathname proj_id init_val.\n",argv[0]);
        return -1;
    }
    key_t sem_key = Ftok(argv[1], atoi(argv[2]));
    printf("sem key = %x\n",sem_key);

    int sem_id = Semget(sem_key, 1, IPC_CREAT|IPC_EXCL|0755);
    printf("sem id = %d\n", sem_id);

    union semun init;
    init.val = atoi(argv[3]);
    semctl(sem_id, 0, SETVAL, init);

    return 0;
}



/*
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main()
{
    int ret;
    key_t sem_key = ftok("mysem", 0xff);
    if(sem_key == -1)
    {
        perror("ftok.");
        exit(1);
    }
    else 
        printf("sem key = %x\n",sem_key);

    int sem_id = semget(sem_key, 1, IPC_CREAT|IPC_EXCL|0755);
    if(sem_id == -1)
    {
        perror("semget");
        exit(1);
    }
    else
        printf("sem id = %d\n",sem_id);

    // value  &&  sem
    union semun init_val;
    init_val.val = 3;
    semctl(sem_id, 0, SETVAL, init_val);


    int sem_val = semctl(sem_id, 0, GETVAL);
    if(sem_val == -1)
    {
        perror("semctl");
    }
    else
        printf("sem init value = %d\n",sem_val);

    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 2;
    op.sem_flg = 0;
    semop(sem_id, &op, 1);
    
    sem_val = semctl(sem_id, 0, GETVAL);
    if(sem_val == -1)
    {
        perror("semctl");
    }
    else
        printf("sem new value = %d\n",sem_val);

    if((ret=semctl(sem_id, 0, IPC_RMID)) == -1)
    {
        printf("Remove sem Fail.\n");
    }
    else
        printf("Remvoe sem OK.\n");

    return 0;
}
*/











