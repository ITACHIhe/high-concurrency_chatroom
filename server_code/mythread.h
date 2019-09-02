#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
// 多线程类，因为不知道为什么C++11的多线程写不出来，写这个是为了接收的时候阻塞不会影响UI的控件不会卡死
//本程序只写了一个多线程，以下的多线程都通指这个类
class Mythread : public QThread
{
    Q_OBJECT
public:
    explicit Mythread(QObject *parent = nullptr);
protected:
    void run();//这个多线程类的入口函数
};

#endif // MYTHREAD_H
