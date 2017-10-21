#ifndef _LOG_H
#define _LOG_H
/**********************************************************
*    > File Name: log.h
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月09日 星期一 21时17分28秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include<stdarg.h>
#include<syslog.h>

void set_loglevel(int level);
void sys_log(int log_level, const char *file_name, int line_num, const char *format, ...);

//#define sys_log(log_level, format) _sys_log(log_level, __FILE__, __LINE__, format)

#endif // _LOG_H
