#ifndef CHIOCE_H
#define CHIOCE_H
#include"mythread.h"
#include <QDialog>
#include<QCloseEvent>
namespace Ui {
class chioce;
}

class chioce : public QDialog
{
    Q_OBJECT

public:
    explicit chioce(QWidget *parent = 0);
    ~chioce();
    Mythread *thread_rec;//生成多线程类的对象
private slots:
    void on_pushButton_clicked();//对应的槽
    void changeddata(int a);//连接人数发生了改变
    void on_close_Button_clicked();

signals:
    void senddata(int);//连接人数发生了改变的信号
private:
    Ui::chioce *ui;//连接人数发生了改变的的槽
    void closeEvent(QCloseEvent *);//窗口关闭事件

    bool isopen;
};

#endif // CHIOCE_H
