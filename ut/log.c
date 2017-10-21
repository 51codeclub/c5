
/**********************************************************
*    > File Name: log.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月09日 星期一 21时19分55秒
**********************************************************/

#include"log.h"

#define LOG_BUFFER_SIZE 256

static int loglevel = LOG_INFO;

static char* loglevels[] = 
{
    "LOG_EMERG!", "LOG_ALERT", "LOG_CRIT", "LOG_ERR","LOG_WARNING","LOG_NOTICE","LOG_INFO","LOG_DEBUG"
};

void set_loglevel(int level)
{
    loglevel = level;
}

//sys_log(LOG_INFO, __FILE__, __LINE__, "%s %d","fjlalfjal",a);

void sys_log(int log_level, const char *file_name, int line_num, const char *format, ...)
{
    if(log_level > loglevel)
        return;

    time_t te;
    time(&te);
    struct tm *cur_time = localtime(&te);

    char buffer[LOG_BUFFER_SIZE];
    memset(buffer, 0, LOG_BUFFER_SIZE);
    strftime(buffer, LOG_BUFFER_SIZE-1," [%x %X ] ",cur_time);

#ifdef LOG_FILE
    FILE *fp = fopen("log/logfile","a");
    fprintf(fp,"%s", buffer);//时间戳
    fprintf(fp,"%s:%04d ", file_name, line_num);
    fprintf(fp,"<%s> ",loglevels[log_level-LOG_EMERG]);
  
#else
    printf("%s", buffer);//时间戳
    printf("%s:%04d ", file_name, line_num);
    printf("<%s> ",loglevels[log_level-LOG_EMERG]);
#endif

    va_list arg_list;
    va_start(arg_list, format);
    memset(buffer, 0, LOG_BUFFER_SIZE);
    vsnprintf(buffer, LOG_BUFFER_SIZE-1, format, arg_list);
#ifdef LOG_FILE
    fprintf(fp,"%s\n",buffer);
    fclose(fp);
#else
    printf("%s\n",buffer);
#endif
    va_end(arg_list);
    fflush(stdout);
}







