#include "widget.h"
#include "ui_widget.h"
#include<QMessageBox>
#include"socket_com.h"
#include<QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    ui->id_line->setClearButtonEnabled(true);
    ui->passwordline->setClearButtonEnabled(true);
    ui->passwordline->setEchoMode(QLineEdit::Password);//设置密码格式
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_login_button_clicked()
{
       QString ID= ui->id_line->text();
       QString pa_wd=ui->passwordline->text();
       if(ID.isEmpty()||pa_wd.isEmpty())
       {
           QMessageBox::warning(0,"警告","密码或者账号为空");
       }
       else
       {
           QString ID_and_PA_WD="ID:"+ID+" "+pa_wd;
           QByteArray ID_and_PA_WD1=ID_and_PA_WD.toLatin1();
           const char * ID_and_PA_WD2=ID_and_PA_WD1.data();
           socket_com *s2=socket_com::getInstance();
           s2->socket_login(ID_and_PA_WD2);

          char tmpbuffer[1024];
          int nn=-1;


           nn=recv(s2->sockfd,tmpbuffer,1024,0);
          if(nn!=-1)
          {
           tmpbuffer[nn]='\0';
           qDebug()<<tmpbuffer;
           QString str = QString(QLatin1String(tmpbuffer));
             if(str=="yesyes")
             {
                 e1.show();
                 this->hide();
             }
             else
             {
                QMessageBox::warning(0,"警告","账号或者密码错误");
                ui->id_line->clear();
                ui->passwordline->clear();
             }
           }
           else
           {
               QMessageBox::warning(0,"警告","无法连接服务器");
               return;
           }




           //这是测试简化
       }
}

void Widget::on_register_button_clicked()
{
    QMessageBox::information(0,"提示","正在申请账号，请按OK键");
    //这是测试简化
    socket_com *s1=socket_com::getInstance();
    s1->socket_start();
    char tmpbuffer[1024];
    int n=-1;
    n=recv(s1->sockfd,tmpbuffer,1024,0);
   if(n!=-1)
   {
     tmpbuffer[n]='\0';
    qDebug()<<tmpbuffer;
    QString str = QString(QLatin1String(tmpbuffer));

     str="账号是"+str+"密码是123";
     QMessageBox::information(0,"提示",str);
    }
    else
    {
        QMessageBox::warning(0,"警告","无法连接服务器");
    }
}
