
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月22日 星期五 15时58分50秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    printf("argc = %d\n",argc);

    int i;
    for(i=0; i<argc; ++i)
    {
        printf("argv[%d] = %s\n",i, argv[i]);
    }
    return 0;
}

/*
#ifdef WIN
void fun()
{
    printf("This is fun windows.\n");
}
#else
void fun()
{
    printf("This is fun linux.\n");
}
#endif

#ifdef xxx
//
#endif

int main()
{
    fun();
    return 0;
}

/*
int Max(int a, int b)
{
    return a > b ? a : b;
}

int Fun(int a, int b, int c)
{
    return Max(Max(a,b),c);
}

int main()
{
    int a = 10;
    int b = 20;
    int c = 15;

    int *p = &a;
    printf("size = %d\n",sizeof(p));

    int ret = Max(a,b);
    ret = Fun(a, b, c);


    return 0;
}
*/
