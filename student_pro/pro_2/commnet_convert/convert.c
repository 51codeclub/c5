
/**********************************************************
*    > File Name: convert.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月23日 星期六 09时46分48秒
**********************************************************/

#include "utili.h"
#include "convertcomment.h"

int main(int argc, char *argv[])
{
    FILE *fpin = fopen("./src_file/input.c", "r");
    if(NULL == fpin)
    {
        printf("open input.c fail.\n");
        return -1;
    }
    FILE *fpout = fopen("./dest_file/output.c", "w");
    if(NULL == fpout)
    {
        printf("open output.c fail.\n");
        return -1;
    }

    convertcomment(fpin, fpout);

    fclose(fpin);
    fclose(fpout);

    printf("Commnet Convert Completion.......\n");
    return 0;
}
