#ifndef _CALC_H
#define _CALC_H
/**********************************************************
*    > File Name: calc.h
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年11月18日 星期六 09时23分38秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

typedef enum {QUIT, ADD, SUB, MUL, DIV, MOD}ENUM_CALC_TYPE;

//op1 op  op2  1 + 2

#define CMD_SIZE 5

typedef struct calcst
{
    int op1;
    int op2;
    ENUM_CALC_TYPE op;
}calcst;

#endif // _CALC_H
