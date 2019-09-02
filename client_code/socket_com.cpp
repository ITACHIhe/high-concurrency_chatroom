#include "socket_com.h"
#include<QDebug>
#include"msgemiter.h"
#include<QMessageBox>
int socket_com::number=0;
socket_com *socket_com::com=socket_com::getInstance();
socket_com::socket_com()
{
    sockfd=0;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(8889);
    strptr="127.0.0.1";
    if(inet_pton(AF_INET, strptr, &servaddr.sin_addr) <= 0)
    {
        qDebug()<<"inet_pton()error";

    }
    iscon=false;
}

int socket_com::socket_start()
{
    if(sockfd==0)
   {
        if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        qDebug()<<"create socket error";
        return 0;
    }
   }
    if(iscon==false)
  {
        if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
         qDebug()<<"connect error()";
         return 0;
    }
  }
     iscon=true;
     const char buf[]="i need ID";
     qDebug()<<"socked1"<<sockfd;
     write(sockfd,buf,strlen(buf));
     return 0;
}

int socket_com::socket_login(const char*mix)
{
    if(sockfd==0)
   {
        if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
         qDebug()<<"create socket error";
        return 0;
    }
   }
    if(iscon==false)
  {
        if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
         qDebug()<<"connect error()";
         return 0;
    }
  }
     iscon=true;
    //
    //发送数据到服务器
     qDebug()<<"socked"<<sockfd;
     write(sockfd,mix,strlen(mix));
     return 0;
}

int socket_com::socket_enter(const char *mix)
{
    qDebug()<<"socked:"<<sockfd;
     write(this->sockfd,mix,strlen(mix));
     qDebug()<<"success to enter chat room";

     return 0;
}
void socket_com::socket_send_file()
{
    FILE *xml_fq;
    if((xml_fq=fopen("data.xml","rb"))==NULL)
    {
        qDebug()<<"文件打开失败";
        exit(0);
    }
    qDebug()<<"open file success";
    memset(buffer,0,sizeof(buffer));
    while (!feof(xml_fq))
    {
       len = fread(buffer, 1, sizeof(buffer), xml_fq);
       if(len != write(sockfd, buffer, len))
       {
           qDebug()<<"写完了";
           break;
       }
    }
    fclose(xml_fq);
}

void socket_com::socket_recv()//这是受到xml回包的做法
{
    char tmpBuffer[2048];
    r1=MsgEmiter::getInstance();
    while(1)
 {

    int recv_num=recv(sockfd,tmpBuffer,2048,0);
    if(recv_num==0)
    {
        qDebug()<<"recv is duankai";
       // r1->sendmsg_close();  it will dead all_process
        QMessageBox::warning(0,"警告","服务器已经断开连接");
        return;

    }
    qDebug()<<recv_num<<endl;

    qDebug()<<tmpBuffer;
    tmp_xml = QString(QLatin1String(tmpBuffer));

    r1->send_msg();
    }
}

