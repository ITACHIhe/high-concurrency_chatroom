#include "choice.h"
#include "ui_choice.h"
#include<QDebug>
#include"socket_com.h"
#include<QMessageBox>

choice::choice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choice)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog| Qt::FramelessWindowHint);

    ui->password_line->setEchoMode(QLineEdit::Password);
    ui->room_line->setClearButtonEnabled(true);
    ui->name_line->setClearButtonEnabled(true);
    ui->password_line->setClearButtonEnabled(true);
    ui->password_line->setEchoMode(QLineEdit::Password);
}

choice::~choice()
{
    delete ui;
}

void choice::on_quit_Button_clicked()
{
    this->close();
}

void choice::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    QPoint y=event->globalPos();
    QPoint x=y-this->z;
    this->move(x);
}

void choice::mousePressEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    QPoint y =event->globalPos();
    QPoint x=this->geometry().topLeft();
    this->z=y-x;
}

void choice::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    this->z=QPoint();
}

void choice::closeEvent(QCloseEvent *)
{
    socket_com *s1=socket_com::getInstance();
    char closebuff[]="00000";
    send(s1->sockfd,closebuff,strlen(closebuff),0);
    ::close(s1->sockfd);
}

void choice::on_enter_Button_clicked()
{


    QString name=ui->name_line->text();
    QString room=ui->room_line->text();
    QString mima=ui->password_line->text();
    if(name.isEmpty()||room.isEmpty())
    {
        QMessageBox::warning(0,"警告","密码或者账号为空");
    }
    else
    {
        m1=new chat_room(name,room);
        m1->show();
        qDebug()<<m1->my_name;
        this->hide();
        QString message=room+" "+name+" "+mima;
        QByteArray message1=message.toLatin1();
        const char * message2=message1.data();
        qDebug()<<message2;
        socket_com *s3=socket_com::getInstance();
         s3->socket_enter(message2);
    }

}
