#ifndef SOCKET_COM_H
#define SOCKET_COM_H
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include"msgemiter.h"
#include<set>
#define MAXLINE 4096

class socket_com
{
private:
    socket_com();
public:
    static socket_com* getInstance()
    {
        if(com==nullptr)
        {
            com=new socket_com;
        }
        ++number;
        return com;
    }

    static socket_com* FreeInstance()
    {
        return com;
    }
    static socket_com *com;
    static int number;

public:
    int socket_start();
    int socket_login(const char *mix);
    int socket_enter(const char *mix);
    void socket_send_file();
    void socket_recv();
public:
    int   sockfd, len;
    char  buffer[MAXLINE];
    struct sockaddr_in  servaddr;
    FILE *fq;
    const char *strptr;
    bool iscon;
    MsgEmiter *r1;
    QString tmp_xml;

    std::set<QString>right_name;

};

#endif // SOCKET_COM_H
