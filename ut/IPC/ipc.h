
/**********************************************************
*    > File Name: ipc.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月28日 星期六 09时15分11秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/msg.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

//////////////////////////////////////////
//1  ftok

key_t Ftok(const char *pathname, int proj_id)
{
    key_t key = ftok(pathname, proj_id);
    if(key == -1)
    {
        perror("ftok.");
        exit(1);
    }
    return key;
}

//////////////////////////////////////////
//2  semget

int Semget(key_t key, int nsems, int semflg)
{
    int id = semget(key, nsems, semflg);
    if(id == -1)
    {
        perror("semget.");
        exit(1);
    }
    return id;
}


//////////////////////////////////////////
//3 Shmget
int Shmget(key_t key, size_t size, int shmflg)
{
    int id = shmget(key, size, shmflg);
    if(id == -1)
    {
        perror("shmget.");
        exit(1);
    }
    return id;
}

void* Shmat(int shmid, const void *shmaddr, int shmflg)
{
    void *addr = shmat(shmid, shmaddr, shmflg);
    if(addr == (void*)-1)
    {
        perror("shmat.");
        exit(1);
    }
    return addr;
}

///////////////////////////////////////////////
int Msgget(key_t key, int msgflg)
{
    int id = msgget(key, msgflg);
    if(id == -1)
    {
        perror("msgget.");
        exit(1);
    }
    return id;
}






