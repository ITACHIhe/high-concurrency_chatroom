#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowFlags(Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);//设置取消最大化的写法
    w.setWindowTitle("高并发聊天室服务器");
    w.show();

    // 固定窗口大小的写法，这个必须在show的后面
    QSize this_size=w.frameSize();
    w.setMaximumSize(this_size);
    w.setMinimumSize(this_size);

    return a.exec();
}
