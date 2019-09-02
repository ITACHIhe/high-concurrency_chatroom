#include "widget.h"
#include <QApplication>
#include<QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//情况2
    QTextCodec::setCodecForLocale(codec);


    QApplication a(argc, argv);
    Widget w;
    w.setWindowFlags(Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    w.setWindowTitle("高并发聊天室客户端");
    w.show();
    QSize this_size=w.frameSize();
    w.setMaximumSize(this_size);
    w.setMinimumSize(this_size);


    return a.exec();
}
