
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月10日 星期五 19时46分30秒
**********************************************************/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

//1 : 1

#define MAX_COUNT 20
#define MAX_BUFFER_SIZE 8
#define OVER -1

typedef struct pc_st
{
    int buffer[MAX_BUFFER_SIZE];
    pthread_mutex_t mutex;
    pthread_cond_t  notfull;
    pthread_cond_t notempty;
    int write_pos;
    int read_pos;
}pc_st;

///////////////////////////////////////////////
pc_st  pc;
void init_pc(pc_st *p)
{
    memset(p->buffer, 0, sizeof(p->buffer));
    pthread_mutex_init(&p->mutex, NULL);
    pthread_cond_init(&p->notfull, NULL);
    pthread_cond_init(&p->notempty, NULL);
    p->write_pos = 0;
    p->read_pos = 0;
}
void destroy_pc(pc_st *p)
{
    pthread_mutex_destroy(&p->mutex);
    pthread_cond_destroy(&p->notfull);
    pthread_cond_destroy(&p->notempty);
    p->write-pos = 0;
    p->read_pos = 0;
}
/////////////////////////////////////////////////
void put(pc_st *p, int val)
{
    p->buffer[p->write_pos] = val;
    p->write_pos++;
}
int  get(pc_st *p)
{
    int val = p->buffer[p->read_pos];
    p->read_pos++;
    return val;
}
/////////////////////////////////////////////////

void* producer(void *arg)
{
    int i;
    for(i=1; i<=MAX_COUNT; ++i)
    {
        put(&pc, i);
    }
    put(&pc, OVER);
}
void* consumer(void *arg)
{
    int value;
    while(1)
    {
        value = get(&pc);
        if(value == OVER)
            break;
        printf("value = %d\n",value);
    }
}

int main()
{
    init_pc(&pc);
    pthread_t pro_id, con_id;
    pthread_create(&pro_id, NULL, producer, NULL);
    sleep(1);
    pthread_create(&con_id, NULL, consumer, NULL);

    pthread_join(pro_id, NULL);
    pthread_join(con_id, NULL);

    destroy_pc(&pc);

    return 0;
}
