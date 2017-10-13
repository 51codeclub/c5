
/**********************************************************
 *    > File Name: copy.c
 *    > Author: 51CC_baosongshan
 *    > Mail: baosongshan2006@163.com 
 *    > Created Time: 2017年10月13日 星期五 14时59分13秒
 **********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

#define PATH_SIZE 100

void help()
{
    printf("This is copy help info.\n");
}

void copy_file(char *src_file, char *dest_file)
{
    FILE *src= fopen(src_file, "r");
    if(src == NULL)
    {
        printf("open %s fail.\n",src_file);
        exit(1);
    }
    FILE *dest = fopen(dest_file, "w");
    if(dest == NULL)
    {
        printf("open %s fail.\n",dest_file);
        exit(1);
    }

    char buffer[128];
    while(!feof(src))
    {
        fgets(buffer, 128, src);
        fputs(buffer, dest);
        memset(buffer, 0, 128);
    }

    fclose(src);
    fclose(dest);
}

void copy_dir(char *src_dir, char *dest_dir)
{
    DIR *dp = opendir(src_dir);

    //
    mkdir(dest_dir, 0755);

    char src_pre_dir[PATH_SIZE];
    char src_cur_dir[PATH_SIZE];
    char dest_pre_dir[PATH_SIZE];
    char dest_cur_dir[PATH_SIZE];

    strcpy(src_pre_dir, src_dir);
    strcpy(src_cur_dir, src_dir);
    strcpy(dest_pre_dir, dest_dir);
    strcpy(dest_cur_dir, dest_dir);

    struct dirent *ptr;
    while( (ptr = readdir(dp)) != NULL)
    {
        if(!strcmp(ptr->d_name,".") || !strcmp(ptr->d_name,".."))
            continue;

        strcat(src_cur_dir, "/");
        strcat(src_cur_dir, ptr->d_name);
        strcat(dest_cur_dir, "/");
        strcat(dest_cur_dir, ptr->d_name);


        struct stat info;
        if(stat(src_cur_dir, &info) < 0)
        {
            perror("stat");
            continue;
        }
        if(S_ISDIR(info.st_mode))
        {
            //strcat(src_cur_dir, "/");
            //strcat(src_cur_dir, ptr->d_name);
            //strcat(dest_cur_dir, "/");
            //strcat(dest_cur_dir, ptr->d_name);
            copy_dir(src_cur_dir, dest_cur_dir);
        }
        else
        {
            //strcat(src_cur_dir, "/");
            //strcat(src_cur_dir, ptr->d_name);
            //strcat(dest_cur_dir, "/");
            //strcat(dest_cur_dir, ptr->d_name);
            copy_file(src_cur_dir, dest_cur_dir);
        }
        strcpy(src_cur_dir, src_pre_dir);
        strcpy(dest_cur_dir, dest_pre_dir);


    }
}

void copy(char *src_file, char *dest_file)
{
    struct stat info;
    stat(src_file, &info);

    if(S_ISDIR(info.st_mode))
    {
        copy_dir(src_file, dest_file);
    }
    else
    {
        copy_file(src_file, dest_file);
    }
}

// ./copy -s src.c -d dest.c

int main(int argc, char *argv[])
{
    char src_file[PATH_SIZE] = {0};
    char dest_file[PATH_SIZE] = {0};

    int option;
    while((option = getopt(argc, argv, "s:d:h")) != -1)
    {
        switch(option)
        {
            case 's':
                strcpy(src_file, optarg);
                break;
            case 'd':
                strcpy(dest_file, optarg);
                break;
            case 'h':
                help();
                break;
        }
    }

    copy(src_file, dest_file); //src_file --> dest_file

    return 0;
}









