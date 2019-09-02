#include "msgemiter.h"
#include<QDebug>
MsgEmiter* MsgEmiter::er=NULL;
MsgEmiter::MsgEmiter(QObject *parent) : QObject(parent)
{

}

void MsgEmiter::send_msg()
{

    emit controlMsg();
}

void MsgEmiter::sendmsg_close()
{
    emit close_to_all();
}
