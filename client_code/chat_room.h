#ifndef CHAT_ROOM_H
#define CHAT_ROOM_H

#include <QDialog>
#include <QTextCharFormat>
#include<QCloseEvent>
namespace Ui {
class chat_room;
}

class chat_room : public QDialog
{
    Q_OBJECT

public:
    explicit chat_room(QString name,QString room_number,QWidget *parent = 0);
     QString text;//这个是临时保存自己输出的文字的
     QString my_name;//这个是保存自己的名字的
     QString localhostname;
      QString my_address;
     QString  my_room_number;
    ~chat_room();

public:
     void write_xml(QString Name,QString Hostname,QString Address,QString room_number);
     void write_xml(QString Name,QString Hostname,QString Address,QString room_number,QString time,QString text_string);
private slots:
    void on_exitButton_clicked();

    void on_sendButton_clicked();
    void wirte_mess();

    void on_clearButton_clicked();



    void on_SizeComboBox_currentIndexChanged(int index);

     void changeddata(int a);//连接人数发生了改变

     void read_to_close();

private:
    Ui::chat_room *ui;
private:
    void closeEvent(QCloseEvent *);
signals:
     void senddata(int);//连接人数发生了改变的信号


};

#endif // CHAT_ROOM_H
