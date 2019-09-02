#ifndef CHOICE_H
#define CHOICE_H

#include <QDialog>
#include<QMouseEvent>
#include<QPoint>
#include"chat_room.h"
#include<QCloseEvent>
namespace Ui {
class choice;
}

class choice : public QDialog
{
    Q_OBJECT

public:
    explicit choice(QWidget *parent = 0);
    ~choice();
    chat_room *m1;

private slots:
    void on_quit_Button_clicked();
    void on_enter_Button_clicked();

private:
    Ui::choice *ui;
     QPoint x,y,z;

private:
   void mouseMoveEvent(QMouseEvent *event);
   void mousePressEvent(QMouseEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);

    void closeEvent(QCloseEvent *);



};

#endif // CHOICE_H
