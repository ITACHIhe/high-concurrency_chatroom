#include "mythread.h"
#include"socket_server.h"
Mythread::Mythread(QObject *parent) : QThread(parent)
{

}
void Mythread::run()
{
    socket_server * r5=socket_server::getInstance();
    r5->socket_rec();
}
