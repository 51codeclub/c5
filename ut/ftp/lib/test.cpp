
/**********************************************************
*    > File Name: test.cpp
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月22日 星期五 14时39分25秒
**********************************************************/


#include<iostream>
#include<stdlib.h>
using namespace std;

void ftp_start()
{
    system("systemctl start vsftpd");
}
void ftp_stop()
{
    system("systemctl stop vsftpd");
}
void ftp_download(string &filename);
void ftp_upload(string &filename);
void ftp_mkdir(string &dirname);
//.........

int main()
{
    ftp_start();
    cout<<"****************************************"<<endl;
    cout<<"* [1] download file   [2] upload fil   *"<<endl;
    cout<<"****************************************"<<endl;
    ftp_stop();
    return 0;
}
