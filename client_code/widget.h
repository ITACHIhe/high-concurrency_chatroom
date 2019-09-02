#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"choice.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    choice e1;
private slots:
    void on_login_button_clicked();

    void on_register_button_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
