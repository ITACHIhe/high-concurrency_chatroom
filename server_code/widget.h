#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"chioce.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    chioce *e1;//生成chioce类的对象
private slots:
    void on_login_button_clicked();//对应的槽
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
