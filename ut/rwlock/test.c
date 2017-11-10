

/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月04日 星期六 09时15分41秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"my_pthread_rwlock.h"

my_pthread_rwlock_t rwlock = MY_PTHREAD_RWLOCK_INITIALIZER;

void clean_up(void *arg)
{
    printf("Clean up Code.\n");
    pthread_rwlock_unlock(&rwlock);
}

void* thread_fun1(void *arg)
{
    my_pthread_rwlock_rdlock(&rwlock);
    printf("This is thread 1.\n");
    pthread_cleanup_push(clean_up, NULL);
    //sleep(3);
    //pthread_exit(NULL);
    pthread_cleanup_pop(1);
    my_pthread_rwlock_unlock(&rwlock);

    //.................

}

void* thread_fun2(void *arg)
{
    my_pthread_rwlock_wrlock(&rwlock);
    printf("This is thread 2.\n");
    printf("thread 2 sleep....\n");
    sleep(5);
    printf("thread 2 wake up.\n");
    my_pthread_rwlock_unlock(&rwlock);
}

void* thread_fun(void *arg)
{
    pthread_t tid = *(pthread_t*)arg;
    pthread_cancel(tid);
}

int main()
{
    pthread_t tid1, tid2, tid;
    //pthread_create(&tid2, NULL, thread_fun2, NULL);
    //sleep(1);
    pthread_create(&tid1, NULL, thread_fun1, NULL);
    sleep(1);

    //pthread_create(&tid, NULL, thread_fun, &tid1);

    //pthread_join(tid, NULL);
    pthread_join(tid1, NULL);
    //pthread_join(tid2, NULL);
    return 0;
}



/*
#define N 5

void* thread_fun(void *arg)
{
    my_pthread_rwlock_wrlock(&rwlock);
    printf("main thread get wrlock,\n");
    sleep(12);
    my_pthread_rwlock_unlock(&rwlock);
}


void* thread_fun1(void *arg)
{
    int index = *(int*)arg;
    printf("This is [%d]thread get rdlock.\n",index);
    my_pthread_rwlock_rdlock(&rwlock);
    printf("[%d] thread get rdlock.\n",index);
    my_pthread_rwlock_unlock(&rwlock);
}
void* thread_fun2(void *arg)
{
    int index = *(int*)arg;
    printf("This is [%d] thread get wrlock.\n",index);
    my_pthread_rwlock_wrlock(&rwlock);
    printf("[%d] thread get wrlock.\n",index);
    my_pthread_rwlock_unlock(&rwlock);
}

int main()
{
    pthread_t tid,tid1[N],tid2[N];

    pthread_create(&tid, NULL, thread_fun, NULL);

    int i;
    for(i=0; i<N; ++i)
    {
        pthread_create(&tid1[i], NULL, thread_fun1, &i);
        sleep(1);
    }
    for(i=0; i<N; ++i)
    {
        pthread_create(&tid2[i], NULL, thread_fun2, &i);
        sleep(1);
    }

    pthread_join(tid, NULL);
    for(i=0; i<N; ++i)
    {
        pthread_join(tid1[i], NULL);
        pthread_join(tid2[i], NULL);
    }
    return 0;
}

/*
#include"my_pthread_rwlock.h"

my_pthread_rwlock_t rwlock = MY_PTHREAD_RWLOCK_INITIALIZER;

void* thread_fun1(void *arg)
{
    my_pthread_rwlock_rdlock(&rwlock);
    printf("1111111111111111111\n");
    //my_pthread_rwlock_unlock(&rwlock);
}
void* thread_fun2(void *arg)
{
    my_pthread_rwlock_wrlock(&rwlock);
    printf("222222222222222222\n");
}

int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread_fun1, NULL);
    sleep(1);
    pthread_create(&tid2, NULL, thread_fun2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
*/







