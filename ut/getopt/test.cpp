
/**********************************************************
 *    > File Name: test.cpp
 *    > Author: 51CC_baosongshan
 *    > Mail: baosongshan2006@163.com 
 *    > Created Time: 2017年09月22日 星期五 14时56分07秒
 **********************************************************/


#include<stdio.h>
#include<iostream>
#include<unistd.h>
using namespace std;

int main(int argc, char *argv[])
{
    opterr = 0;
    char ch;
    while((ch = getopt(argc, argv, "a:b:x:hji")) != -1)
    {
        switch(ch)
        {
            case 'a':
                cout<<"This is a option : a="<<optarg<<endl;
                break;
            case 'b':
                cout<<"This is b option : b="<<optarg<<endl;
                break;
            case 'x':
                cout<<"This is x :>"<<optarg<<endl;
                break;
            case 'h':
                cout<<"This is h option."<<endl;
                break;
            case 'j':
                cout<<"This is j option"<<endl;
                break;
            case 'i':
                cout<<"This is i option"<<endl;
                break;
            case ':':
                cout<<"less option."<<endl;
                break;
            case '?':
                cout<<"option error, invalid option is:>"<<(char)optopt<<endl;
                break;
        }
    }
    return 0;
}
