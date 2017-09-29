
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月29日 星期五 14时39分52秒
**********************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>

int main()
{
    char path[100];
    memset(path, 0, 100);

    getcwd(path, 100);

    DIR *dirp = opendir(path);

    struct dirent *ptr;
    while((ptr = readdir(dirp)) != NULL)
    {
        printf("%s ",ptr->d_name);
    }
    printf("\n");

    closedir(dirp);

    return 0;
}
/*int main()
{
    char path[100];
    memset(path, 0, 100);

    char *ret = getcwd(path, 100);
    printf("ret = %s\n",ret);
    printf("path = %s\n",path);

    return 0;
}

/*
int main()
{
    int fd = open("myfile.txt", O_WRONLY);
    //close(STDOUT_FILENO);
    //int fd1 = dup(fd);
    int fd1 = dup2(fd, STDOUT_FILENO );
    printf("fd1 = %d\n",fd1);

    printf("flaflkajlkfjalkfjalfjal\n");
    printf("jflkalkf fjflaf fajlfajlf");

    return 0;
}

/*
int main(int argc, char *argv[])
{
    //int fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0755);
    //int fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR|S_IWUSR|S_IXUSR|S_IROTH|S_IXOTH);
    int fd = open(argv[1], O_WRONLY , S_IRUSR|S_IWUSR|S_IXUSR|S_IROTH|S_IXOTH);

    char *s1 = "hello linux.";
    int nbytes = write(fd, s1, strlen(s1));
    printf("nbyts = %d\n",nbytes);

    char *s2 = "hello C++.";
    lseek(fd, 20, SEEK_SET);
    write(fd, s2, strlen(s2));

    close(fd);
    return 0;
}

/*
//openfile myfile.txt

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("usge: openfile filename.\n");
        return -1;
    }

    int fd = open(argv[1], O_WRONLY); //
    if(fd == -1)
    {
        printf("open %s fail.\n",argv[1]);
    }
    else
    {
        printf("fd = %d\n",fd);
    }


    char *buf1 = "Hello Linux.";
    write(fd, buf1, strlen(buf1));

    close(fd);

    fd = open(argv[1], O_WRONLY);
    char *buf2 = "Hello C.";
    write(fd, buf2, strlen(buf2));
    close(fd);
    return 0;
}

/*
int main()
{
    FILE *fp = fopen("myfile.txt", "w");
    if(NULL == fp)
    {
        printf("Open file fail.\n");
        return -1;
    }

    //fprintf();
    //fcanf();
    //fgetc();
    //fputc();
    //fgets();
    //fputs();
    //fwrite();
    //fread();
    //fseek();
    //rewind();

    fclose(fp);
    return 0;
}
*/
