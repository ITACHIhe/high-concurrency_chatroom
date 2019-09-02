#include "chioce.h"
#include "ui_chioce.h"
#include"socket_server.h"
#include <unistd.h>
#include<QMessageBox>
chioce::chioce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chioce)
{
    ui->setupUi(this);
    thread_rec=new Mythread;//分配多线程对象的内存空间
    connect(ui->close_Button,&QPushButton::clicked,thread_rec,&Mythread::exit);//这个关闭socket的信号与槽的连接，但是没有用
    this->setWindowTitle("高并发聊天室服务器");
    connect(this,SIGNAL(senddata(int)),this,SLOT(changeddata(int)));//人数改变的信号与槽的连接
    isopen=false;
}

chioce::~chioce()
{
    delete ui;
}
void chioce::on_pushButton_clicked()
{
    if(!isopen)
   {
    ui->title_label->setText("服务器已开启");
    socket_server *s11=socket_server::getInstance();
    QMessageBox::information(0,"提示","服务器开启");
    s11->socket_log("服务器已开启");
    isopen=true;

    thread_rec->start();//多线程类的起始函数
   }
    else
    {
        QMessageBox::information(0,"提示","服务器已经开启过了");
    }

}


void chioce::changeddata(int a)
{
    QString tmp="当前连接人数："+QString::number(a)+"人";
    this->ui->sum_label->setText(tmp);
}

void chioce::closeEvent(QCloseEvent *)
{
     socket_server *r12=socket_server::getInstance();
     r12->socket_log("close server windows");
     r12->socker_close();
}



void chioce::on_close_Button_clicked()
{
    socket_server *r12=socket_server::getInstance();
    r12->socker_close();
    isopen=false;
    thread_rec->quit();
}
