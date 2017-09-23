
/**********************************************************
*    > File Name: convertcomment.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月23日 星期六 09时55分30秒
**********************************************************/

#include "convertcomment.h"

//定义状态
typedef enum
{
    no_comment_state,
    c_comment_state,
    cpp_comment_state,
    end_state
}enum_state;

//定义状态机
typedef struct
{
    FILE *input;
    FILE *output;
    enum_state ulstate;
}state_machine;

//定义全局状态机
state_machine g_state;

int convertcomment(FILE *inputfile, FILE *outputfile)
{
    if(inputfile==NULL || outputfile==NULL)
    {
        printf("invalid arugment inputfile or outputfile.\n");
        return -1;
    }

    /////////////////////////////////////////////////////////
    //初始化状态机
    g_state.input = inputfile;
    g_state.output = outputfile;
    g_state.ulstate = no_comment_state;

    char ch;
    while(g_state.ulstate != end_state)
    {
        ch = fgetc(g_state.input);
        eventpro(ch);
    }

    return 0;
}

void eventpro(char ch)
{
    switch(g_state.ulstate)
    {
    case no_comment_state:
        eventpro_no(ch);
        break;
    case c_comment_state:
        break;
    case cpp_comment_state:
        eventpro_cpp(ch);
        break;
    }
}

void eventpro_no(char ch)
{
    char nextch;
    switch(ch)
    {
    case '/':
        nextch = fgetc(g_state.input);
        if(nextch == '/')   //C++
        {
            fputc('/', g_state.output);
            fputc('*', g_state.output);
            g_state.ulstate = cpp_comment_state;
        }
        break;
    }
}

void eventpro_cpp(char ch)
{
    switch(ch)
    {
    case EOF:
        fputc('*', g_state.output);
        fputc('/', g_state.output);
        g_state.ulstate = end_state;
        break;
    default:
        fputc(ch, g_state.output);
        break;
    }
}

























