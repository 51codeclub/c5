
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月21日 星期六 09时07分25秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[], char **env)
{
    //execl("/bin/ls","ls",NULL);
    //execlp("ls","ls",NULL);
    //execle("/bin/ls","ls","-al",NULL);
    //
    char *envp[] = {"ls","-al",NULL};
    execv("/bin/ls",envp);
    return 0;
}
