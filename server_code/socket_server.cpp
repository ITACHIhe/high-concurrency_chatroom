#include "socket_server.h"
#include<QDebug>
#include<QFile>
#include<QTextStream>
#include<set>
#include<QDateTime>
socket_server *socket_server::server=NULL;//单例模式的写法
socket_server::socket_server()
{
    m_worker_connections=1024;//初始化epoll连接的最大项数
    sockfd=0;//初始化socket套接字的句柄
    memset(&servaddr,0,sizeof(servaddr));//结构体清零
    memset(&servaddr_c,0,sizeof(servaddr_c));//结构体清零

    servaddr.sin_family = PF_INET;//设置套接字的信息
    servaddr.sin_port = htons(SERVER_PORT);//设置套接字的信息
    servaddr.sin_addr.s_addr = inet_addr(SERVER_HOST);//设置套接字的信息

     log_name="./ID.txt";//初始化ID文件的名字
     file=new QFile(log_name);//
     new_password="123";//初始化新ID的通用密码

     QDateTime current_date_time=QDateTime::currentDateTime();
     QString current_date=current_date_time.toString("yyyy.MM.dd");
     log_operate="./"+current_date+"oper.log";//生成名字是当天的日志名
     file_operate=new QFile(log_operate);//为日志文件分配空间

}

void socket_server::socket_start()
{
     if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
     {
         qDebug()<<"生成socket失败";
     }
     qDebug()<<"生成socket成功";
     //防止因为timewait情况而使得某个端口无法绑定的情况
     int flag = 1;
     setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
     ref=bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
     if(ref<0)
     {
         qDebug()<<"绑定失败";
     }
       qDebug()<<"绑定成功";
     int tmp;
     tmp=listen(sockfd,5);
     if(tmp<0)
     {
         qDebug()<<"监听失败";
     }
      qDebug()<<"监听成功";
}

void socket_server::epoll_init()
{
      m_epollhandle = epoll_create(m_worker_connections);
      if(m_epollhandle==-1)
      {
          qDebug()<<"epoll初始化失败";
          exit(2);
      }
}

void socket_server::socket_rec()
{




     fd_set rfds;
     std::set<int>fdset;// 保存所有的文件描述符
     fdset.insert(sockfd);
     while(1)
     {

         FD_ZERO(&rfds);
         for(int fd:fdset)
         {
            FD_SET(fd,&rfds);

         }
         int ret = select(*fdset.rbegin()+1, &rfds, NULL, NULL, NULL);
         if(ret>0)
         {
             for(int fd:fdset)
             {
                 if(fd==sockfd&&FD_ISSET(fd, &rfds))
                 {
                     struct sockaddr_in client;
                     socklen_t addrlen = sizeof(client);
                     int cfd = -1;
                     if (-1 == (cfd = accept(sockfd, (struct sockaddr*)&client, &addrlen)))
                       {
                         qDebug()<<"cfd accept error";
                         exit(1);
                       }

                     FD_SET(cfd, &rfds);
                     fdset.insert(cfd);
                     qDebug()<<"new connection"<<cfd;
                 }
                 else if(FD_ISSET(fd, &rfds))
                 {
                     memset(ReadBuffer,0,sizeof(ReadBuffer));
                     int lenrecv=-1;
                     lenrecv=recv(fd,ReadBuffer,2048,0);
                     if(lenrecv>0)
                     {
                         qDebug()<<ReadBuffer;
                         char tmp[]="i need ID";
                         int tmp1=strcmp(ReadBuffer,tmp);
                          if(tmp1==0)//收到客户端申请账号的请求
                          {
                              qDebug()<<"he need ID";
                              QString tmp_ID=create_ID();
                              QByteArray tmp_ID1=tmp_ID.toLatin1();
                              const char * tmp_ID2=tmp_ID1.data();
                              write(fd,tmp_ID2,sizeof(tmp_ID2));
                          }
                          if(ReadBuffer[0]=='I')//收到对方账号登录
                          {
                              if(file->isOpen())//debug出文件会在这里打开，又找不到错误，就在这里弄个判断
                              {
                                  file->close();
                              }
                              qDebug()<<"ReadBuffer"<<ReadBuffer;
                              bool tmp_panduan=check_ID(ReadBuffer);
                              if(tmp_panduan)
                              {
                                  emit e1->senddata(fdset.size()-1);
                                  qDebug()<<"tmp_panduan is ture";
                                  char panduan_password[]="yesyes";
                                  write(fd,panduan_password,sizeof(panduan_password));
                              }
                              else
                              {
                                    qDebug()<<"tmp_panduan is false";
                                  char panduan_password[]="NONO";
                                  write(fd,panduan_password,sizeof(panduan_password));
                              }
                          }
                          if(ReadBuffer[0]=='<')
                          {
                              std::set<int>fdset_re=fdset;//这个相当于TCP广播
                              fdset_to_close=fdset_re;
                              fdset_re.erase(sockfd);

                              fdset_re.erase(fd);//这个使发送者不必收到自己发送的那部分

                              for(int xml_fd:fdset_re)
                              {                            
                              send(xml_fd,ReadBuffer,strlen(ReadBuffer),0);
                              qDebug()<<tmp;
                              }
                          }
                          if(ReadBuffer[0]=='0'&&ReadBuffer[1]=='0'&&ReadBuffer[2]=='0'&&ReadBuffer[3]=='0'&&ReadBuffer[4]=='0')
                          {
                              qDebug()<<"this fd:"<<fd<<"want close";
                          }
                     }
                     else if(0 == lenrecv)//recv为0代表连接关闭
                     {
                         fdset.erase(fd);
                         emit e1->senddata(fdset.size()-1);
                         FD_CLR(fd, &rfds);                        
                         close(fd);
                     }
                     else
                     {
                        qDebug()<<"error";
                     }
                 }
             }
         }
         else
         {
            qDebug()<<"select error";
         }

     }


    /*  这是普通socket写法的打底
   int cfd;//监听套接字
   socklen_t  a=sizeof(servaddr_c);
   cfd=accept(sockfd,(struct sockaddr*)&servaddr_c,&a);
   while (1)//need to duo xian cheng
   {

       if(cfd<0)
       {
           qDebug()<<"fcd没有获得监听套接字";
           continue;
       }
       int n;
       n=recv(cfd,ReadBuffer,2048,0);
       ReadBuffer[n]='\0';
       qDebug()<<"fcd获得监听套接字";
       char tmp[]="i need ID";
       int tmp1=strcmp(ReadBuffer,tmp);
        if(tmp1==0)//收到客户端申请账号的请求
        {
            qDebug()<<"he need ID";
            QString tmp_ID=create_ID();
            QByteArray tmp_ID1=tmp_ID.toLatin1();
            const char * tmp_ID2=tmp_ID1.data();
            write(cfd,tmp_ID2,sizeof(tmp_ID2));
        }
        if(ReadBuffer[0]=='I')//收到对方账号登录
        {
            qDebug()<<"ReadBuffer"<<ReadBuffer;
            bool tmp_panduan=check_ID(ReadBuffer);
            if(tmp_panduan)
            {
                qDebug()<<"tmp_panduan is ture";
                char panduan_password[]="yesyes";
                write(cfd,panduan_password,sizeof(panduan_password));
            }
            else
            {
                  qDebug()<<"tmp_panduan is false";
                char panduan_password[]="NONO";
                write(cfd,panduan_password,sizeof(panduan_password));
            }
        }
   }
*/
}

QString socket_server::create_ID()
{
    qDebug()<<"start create_ID";
    int ID_num=0;
    file->open(QFile::Text|QFile::ReadWrite);
    if(file->exists())
    {
        qDebug()<<"create file successs";
    }
    else
    {
        qDebug()<<"can't create file";
    }

    QTextStream in(file);
    while (!in.atEnd())
    {

        QString line = in.readLine();
        ID_num++;
        qDebug()<<line;
    }
    QString new_ID="000"+QString::number(ID_num);
    qDebug()<<"new ID and password:"<<new_ID<<" "<<new_password;
    file->close();
    file->open(QFile::Text|QFile::ReadWrite|QIODevice::Append);
    if(file->exists())
    {
        qDebug()<<"create file successs again";
    }
    else
    {
        qDebug()<<"can't create file again ";
    }
     QTextStream out(file);
     out<<new_ID<<" "<<new_password<<endl;
     file->close();
     return new_ID;

}

bool socket_server::check_ID(char * ID)
{

    char *tmp_check_ID=ID;
    QString str = QString(QLatin1String(tmp_check_ID));

     file->open(QFile::Text|QFile::ReadOnly);
     if(file->exists())
     {
         qDebug()<<"create file successs in  Check_ID";
     }
     else
     {
         qDebug()<<"can't create file in  Check_ID";
     }
     QTextStream in(file);
     bool is_right=false;
     while (!in.atEnd())
     {
        int a=0;
        qDebug()<<"in.atend:"<<++a;
        QString line = in.readLine();
        QString line2="ID:"+line;
         if(line2==str)
         {
             is_right=true;
             qDebug()<<"password is right";
             return is_right;
         }

         qDebug()<<line;
     }
     file->close();
     return is_right;

}

void socket_server::socket_log(QString op)
{
    file_operate->open(QFile::Text|QFile::ReadWrite|QIODevice::Append);
    if(file_operate->exists())
    {
        qDebug()<<"create log_file successs again";
    }
    else
    {
        qDebug()<<"can't log_create file again ";
    }
      QTextStream in(file_operate);
      QDateTime current_date_time=QDateTime::currentDateTime();
      QString current_date=current_date_time.toString("yyyy.MM.dd hh:mm:ss");
      in<<current_date<<":"<<endl;
      in<<op<<endl;
      file_operate->close();

}

void socket_server::socker_close()
{
    for(int tmp_fd: fdset_to_close)
    {
        char *tmp_send="server ready to close";
        send(tmp_fd,tmp_send,strlen(tmp_send),0);
        ::shutdown(tmp_fd,SHUT_RDWR);
    }
}


