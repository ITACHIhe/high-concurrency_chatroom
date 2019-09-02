#include "widget.h"
#include "ui_widget.h"
#include"socket_server.h"
#include<QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_login_button_clicked()
{
    socket_server *r1=socket_server::getInstance();
    r1->socket_start();

    e1=new chioce();
    e1->show();
    r1->e1=e1;
    QSize this_size=e1->frameSize();
    e1->setMaximumSize(this_size);
    e1->setMinimumSize(this_size);
    this->hide();
}
