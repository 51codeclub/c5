
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月03日 星期五 14时14分03秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

#define COUNT 10
static  int   i = 1;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  even  = PTHREAD_COND_INITIALIZER;
pthread_cond_t  uneven = PTHREAD_COND_INITIALIZER;

//1 3 5 7 9
void* A_fun(void *arg)
{
    while(i <= COUNT)
    {
        pthread_mutex_lock(&mutex);
        if(i % 2 != 0)
        {
            printf("In A fun : %d\n",i);
            ++i;
            pthread_cond_signal(&uneven);
        }
        else 
            pthread_cond_wait(&even, &mutex);
        pthread_mutex_unlock(&mutex);
    }
}
//2 4 6 8 10
void* B_fun(void *arg)
{
    while(i <= COUNT)
    {
        pthread_mutex_lock(&mutex);
        if(i % 2 == 0)
        {
            printf("In B fun : %d\n",i);
            ++i;
            pthread_cond_signal(&even);
        }
        else
            pthread_cond_wait(&uneven, &mutex);
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, A_fun, NULL);
    pthread_create(&tid2, NULL, B_fun, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}

/*
#define N 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t  cond1 = PTHREAD_COND_INITIALIZER;

void* thread_fun(void *arg)
{
    int index = *(int*)arg;
    pthread_mutex_lock(&mutex);
    printf("This is [%d] thread. Sleep......\n",index);
    //pthread_cond_wait(&cond, &mutex);
    pthread_cond_timedwait();
    printf("[%d] thread wake up.\n",index);
    pthread_mutex_unlock(&mutex);
}
void* signal_thread(void *arg)
{
    //pthread_cond_signal(&cond);
    pthread_cond_broadcast(&cond);
}
int main()
{
    pthread_t tid[N];
    int i;
    for(i=0; i<N; ++i)
    {
        pthread_create(&tid[i], NULL, thread_fun, &i);
        sleep(1);
    }

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, signal_thread, NULL);
    for(i=0; i<N; ++i)
    {
        pthread_join(tid[i], NULL);
    }
    pthread_join(thread_id, NULL);
    return 0;
}


/*
void* thread_fun1(void *arg)
{
    pthread_mutex_lock(&mutex);
    printf("This is thread 1 fun.\n");
    sleep(2);
    pthread_cond_wait(&cond, &mutex);
    printf("thread 1 finish.\n");
    //pthread_mutex_unlock(&mutex);
}
void* thread_fun2(void *arg)
{
    int ret = pthread_mutex_lock(&mutex);
    printf("This is thread 2 fun.\n");
    printf("thread 2 finish.\n");
    pthread_cond_signal(&cond);
    printf("thread 2 signal thread 1.\n");
    sleep(3);
    printf("aaaaaaaaaaaaa\n");
    pthread_mutex_unlock(&mutex);
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

/*
#define MAX_THREAD_NUM 100

void* thread_fun(void *arg)
{
    int n = *(int *)arg;
    printf("This is [%d] Thread.\n", n);
    pthread_exit(NULL);
}

void* thread_fun1(void *arg)
{}
void* thread_fun2(void *arg)
{}

int main()
{
    pthread_t tid[MAX_THREAD_NUM];
    int i;
    for(i=0; i<MAX_THREAD_NUM; ++i)
    {
        pthread_create(&tid[i], NULL, thread_fun, &i);
        sleep(1);
    }

    for(i=0; i<MAX_THREAD_NUM; ++i)
    {
        pthread_join(tid[i], NULL);
    }
    return 0;
}

/*
void* thread_fun(void *arg)
{
    int n = *(int*)arg;
    printf("in thread_fun tid = %d\n",pthread_self());
    int i;
    for(i=0; i<n; ++i)
    {
        printf("This is Child Thread.\n");
    }
    pthread_exit("Child Thread Exit Code:Finish.");
    //return xxxx;
}

int main()
{
    pthread_t tid;
    int n = 2;
    int ret = pthread_create(&tid, NULL, thread_fun, &n);
    if(ret != 0)
    {
        printf("create thread fail.\n");
        exit(1);
    }
    else
    {
        printf("child tid = %d\n",tid);
    }
    int i;
    for(i=0; i<10; ++i)
    {
        printf("This is Main Thread.\n");
    }

    char *exit_code;
    pthread_join(tid, (void**)&exit_code);
    printf("In Main Thread: Exit_Code:> %s\n",exit_code);

    return 0;
}

/*
int main()
{
    pthread_t tid = pthread_self();
    printf("tid = %d\n",tid);
    return 0;
}
*/
