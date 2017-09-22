#ifndef _FTP_H
#define _FTP_H
/**********************************************************
*    > File Name: ftp.h
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月22日 星期五 14时51分51秒
**********************************************************/

#include<stdlib.h>
#include<string>

int ftp_start()
{
    int res = system("systemctl start vsftpd");
    return res; //0
}
int ftp_stop()
{
    int res = system("systemctl stop vsftpd");
    return res;
}
                //const char *filename
int ftp_download(string &filename);
int ftp_upload(string &filename);

#endif // _FTP_H
