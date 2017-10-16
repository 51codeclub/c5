#include"utili.h"
#include"convertcomment.h"

int main(int argc,char *argv[])
{
	FILE *fpin=fopen("./src_file/input.c","r");
	if(NULL==fpin)
	{
		printf("open input.c fail\n");
		return -1;
	}
	FILE *fpout=fopen("./dest_file/output.c","w");
	if(NULL==fpout)
	{
		printf("open output.c fail.\n");
		return -1;
	}
	
	convertcomment(fpin,fpout);
	
	fclose(fpin);
	fclose(fpout);

	printf("Comment Convert Completion...........\n");
	return 0;
}
