#ifndef MSGEMITER_H
#define MSGEMITER_H

#include <QObject>

class MsgEmiter : public QObject//定义这个傻逼东西是因为mythread无法继承QOBject,就无法写信号
{
    Q_OBJECT
public:
    explicit MsgEmiter(QObject *parent = nullptr);

    void send_msg();
    void sendmsg_close();
    static MsgEmiter* getInstance()
    {
        if(er==nullptr)
        {
            er=new MsgEmiter;
        }
        return er;
    }

    static MsgEmiter* er;
signals:
    void controlMsg();
    void close_to_all();
public slots:
};

#endif // MSGEMITER_H
