#include "mythread.h"
#include"socket_com.h"
MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run()
{
    socket_com * s9=socket_com::getInstance();
    s9->socket_recv();
}
