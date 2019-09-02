#include "chat_room.h"
#include "ui_chat_room.h"
#include<QMessageBox>
#include<QDateTime>
#include<QtNetwork/QtNetwork>
#include"tinyxml.h"
#include<string>
#include"socket_com.h"
#include"mythread.h"
#include"msgemiter.h"
#include<QDebug>
#include<set>
chat_room::chat_room(QString name,QString room_number,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat_room)
{
    ui->setupUi(this);
    text="";
    //这个是写右边的东西
    ui->userTableWidget->setRowCount(1);//表格15行
    ui->userTableWidget->setColumnCount(3);//表格3列

    this->my_name=name;
    this->my_room_number=room_number;
    ui->userTableWidget->setItem(0,0,new QTableWidgetItem(name));//第几行第几列写什么东西

     localhostname=QHostInfo::localHostName();
    ui->userTableWidget->setItem(0,1,new QTableWidgetItem(localhostname));

    QHostInfo info=QHostInfo::fromName(localhostname);

    foreach(QHostAddress address,info.addresses())//info.address是list，要遍历找出数与ipV4的地址
        {
             if(address.protocol() == QAbstractSocket::IPv4Protocol)
             {
                 qDebug() << address.toString();
                 my_address=address.toString();
             }
        }
    ui->userTableWidget->setItem(0,2,new QTableWidgetItem(my_address));
    write_xml(name,localhostname,my_address,room_number);

    this->setWindowTitle("高并发聊天室客户端");
    QSize this_size=this->frameSize();
    this->setMaximumSize(this_size);
    this->setMinimumSize(this_size);

    MyThread *thread_recv =new MyThread();
    thread_recv->start();

    ui->userTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    MsgEmiter *r2=MsgEmiter::getInstance();
    connect(r2,&MsgEmiter::controlMsg,this,&chat_room::wirte_mess);
    connect(r2,&MsgEmiter::close_to_all,this,&chat_room::read_to_close);



    connect(this,SIGNAL(senddata(int)),this,SLOT(changeddata(int)));//人数改变的信号与槽的连接

}

chat_room::~chat_room()
{
    delete ui;
}

void chat_room::write_xml(QString Name,QString Hostname,QString Address,QString room_number)
{
    //中文乱码，因为tingXML是const char * ,无法自行转换，可以尝试换QT自带的XML
    QByteArray name1=Name.toLatin1();//这几行是将QString转换成从const char*
    const char * name2=name1.data();
    QByteArray localhostname1=Hostname.toLatin1();
    const char * localhostname2=localhostname1.data();
    QByteArray my_address1=Address.toLatin1();
    const char * my_address2=my_address1.data();
    QByteArray room_number1=room_number.toLatin1();
    const char * room_number2=room_number1.data();

    TiXmlDocument* myDocument = new TiXmlDocument();                        //创建一个XML文件
    TiXmlDeclaration *pDeclaration=new TiXmlDeclaration("1.0","UTF-8","");  //创建xml文件头（<?xml version="1.0" encoding="UTF-8" ?>）
    myDocument->LinkEndChild(pDeclaration);                                 //加入将xml文件头加入文档中
    TiXmlElement* BUSINESS = new TiXmlElement("ALL");                    //创建一个元素节点
    myDocument->LinkEndChild(BUSINESS);                                     //加入元素节点到文档中
    TiXmlElement *xml_room = new TiXmlElement("ROOMNUMBER");
    TiXmlElement *xml_name = new TiXmlElement("NAME");                    //创建两个节点
    TiXmlElement *xml_host = new TiXmlElement("HOST");
    TiXmlElement* xml_address = new TiXmlElement("ADDRESS");
    TiXmlElement* xml_time = new TiXmlElement("TIME");
    TiXmlElement* xml_string = new TiXmlElement("STRING");
    BUSINESS->LinkEndChild(xml_room);
    BUSINESS->LinkEndChild(xml_name);                                         //将新建的节点加到下一级
    BUSINESS->LinkEndChild(xml_host);
    BUSINESS->LinkEndChild(xml_address);
    BUSINESS->LinkEndChild(xml_time);
    BUSINESS->LinkEndChild(xml_string);
    TiXmlText *text_room = new TiXmlText(room_number2);
    TiXmlText *text_name = new TiXmlText(name2);                            //添加节点内的文本
    TiXmlText *text_host = new TiXmlText(localhostname2);
    TiXmlText* text_address = new TiXmlText(my_address2);
    TiXmlText* text_time = new TiXmlText("");
    TiXmlText* text_string = new TiXmlText("");
    xml_room->LinkEndChild(text_room);
    xml_name->LinkEndChild(text_name);
    xml_host->LinkEndChild(text_host);
    xml_address->LinkEndChild(text_address);
    xml_time->LinkEndChild(text_time);
    xml_string->LinkEndChild(text_string);
    myDocument->SaveFile("data.xml");                                       //保存xml
}

void chat_room::write_xml(QString Name,QString Hostname,QString Address,QString room_number,QString time,QString text_string111)
{
    //中文乱码，因为tingXML是const char * ,无法自行转换，可以尝试换QT自带的XML
    QByteArray name1=Name.toLatin1();//这几行是将QString转换成从const char*
    const char * name2=name1.data();
    QByteArray localhostname1=Hostname.toLatin1();
    const char * localhostname2=localhostname1.data();
    QByteArray my_address1=Address.toLatin1();
    const char * my_address2=my_address1.data();
    QByteArray room_number1=room_number.toLatin1();
    const char * room_number2=room_number1.data();
    QByteArray time1=time.toLatin1();
    const char * time2=time1.data();
    QByteArray text_string1=text_string111.toLatin1();
    const char * text_string2=text_string1.data();

    TiXmlDocument* myDocument1 = new TiXmlDocument();                        //创建一个XML文件
    TiXmlDeclaration *pDeclaration=new TiXmlDeclaration("1.0","UTF-8","");  //创建xml文件头（<?xml version="1.0" encoding="UTF-8" ?>）
    myDocument1->LinkEndChild(pDeclaration);                                 //加入将xml文件头加入文档中
    TiXmlElement* BUSINESS = new TiXmlElement("ALL");                    //创建一个元素节点
    myDocument1->LinkEndChild(BUSINESS);                                     //加入元素节点到文档中
    TiXmlElement *xml_room = new TiXmlElement("ROOMNUMBER");
    TiXmlElement *xml_name = new TiXmlElement("NAME");                    //创建两个节点
    TiXmlElement *xml_host = new TiXmlElement("HOST");
    TiXmlElement* xml_address = new TiXmlElement("ADDRESS");
    TiXmlElement* xml_time = new TiXmlElement("TIME");
    TiXmlElement* xml_string = new TiXmlElement("STRING");
    BUSINESS->LinkEndChild(xml_room);
    BUSINESS->LinkEndChild(xml_name);                                         //将新建的节点加到下一级
    BUSINESS->LinkEndChild(xml_host);
    BUSINESS->LinkEndChild(xml_time);
    BUSINESS->LinkEndChild(xml_address);

    BUSINESS->LinkEndChild(xml_string);


    TiXmlText *text_room = new TiXmlText(room_number2);
    TiXmlText *text_name = new TiXmlText(name2);                            //添加节点内的文本
    TiXmlText *text_host = new TiXmlText(localhostname2);
    TiXmlText* text_address = new TiXmlText(my_address2);
    TiXmlText* text_time = new TiXmlText(time2);
    TiXmlText* text_string = new TiXmlText(text_string2);
    xml_room->LinkEndChild(text_room);
    xml_name->LinkEndChild(text_name);
    xml_host->LinkEndChild(text_host);
    xml_address->LinkEndChild(text_address);
    xml_time->LinkEndChild(text_time);
    xml_string->LinkEndChild(text_string);
    myDocument1->SaveFile("data.xml");                                       //保存xml
}

void chat_room::on_exitButton_clicked()
{
    this->close();
}

void chat_room::on_sendButton_clicked()
{
    if(ui->messageTextEdit->toPlainText() == "")
    {
        QMessageBox::warning(0,tr("警告"),tr("发送内容不能为空"),QMessageBox::Ok);
        return;
    }
    else
    {
         text=ui->messageTextEdit->toPlainText();
         ui->messageTextEdit->clear();
         QDateTime current_date_time=QDateTime::currentDateTime();
         QString current_date=current_date_time.toString("yyyy.MM.dd hh:mm:ss");

         ui->messageBrowser->append(this->my_name+"            "+current_date);
         ui->messageBrowser->append(text);
         write_xml(my_name,localhostname,my_address,my_room_number,current_date,text);
         socket_com *s4=socket_com::getInstance();
        s4->socket_send_file();
    }


}

void chat_room::wirte_mess()
{
    socket_com *s2=socket_com::getInstance();
    QFile file("./data1.xml");
    file.open(QFile::Text|QFile::ReadWrite);
    if(file.exists())
    {
        qDebug()<<"create file successs in  Check_ID";
    }
    else
    {
        qDebug()<<"can't create file in  Check_ID";
    }
     QTextStream in(&file);
    in<<s2->tmp_xml;
    file.close();
     TiXmlDocument doc;
     if(!doc.LoadFile("data1.xml"))
     {
         qDebug()<<"加载XML文件失败";
         const char *errorStr = doc.ErrorDesc();
         qDebug()<<errorStr; //打印失败原因；
     }
     else
     {
          qDebug()<<"加载XML文件success";
          TiXmlElement *root = doc.FirstChildElement();
          TiXmlElement *child_str = root->FirstChildElement("STRING");
          TiXmlElement *child_name = root->FirstChildElement("NAME");
          TiXmlElement *child_time = root->FirstChildElement("TIME");
          QString str=child_str->GetText();
          QString name=child_name->GetText();
          QString time=child_time->GetText();

          ui->messageBrowser->append(name+"            "+time);
          ui->messageBrowser->append(str);


          TiXmlElement *child_address = root->FirstChildElement("ADDRESS");
          TiXmlElement *child_HOST = root->FirstChildElement("HOST");
          QString address=child_address->GetText();
          QString host=child_HOST->GetText();
          socket_com *r1=socket_com::getInstance();
          if(r1->right_name.find(name)==r1->right_name.end())
          {

          r1->right_name.insert(name);
           emit changeddata(r1->right_name.size()+1);
          //这部分将信息填写在右边表格里
          int RowCont;
          RowCont=ui->userTableWidget->rowCount();
          ui->userTableWidget->insertRow(RowCont);//增加一行

          //插入元素
          ui->userTableWidget->setItem(RowCont,0,new QTableWidgetItem(name));
          ui->userTableWidget->setItem(RowCont,1,new QTableWidgetItem(host));
          ui->userTableWidget->setItem(RowCont,2,new QTableWidgetItem(address));

          }
     }

}


void chat_room::on_clearButton_clicked()
{
    ui->messageBrowser->clear();
}



void chat_room::on_SizeComboBox_currentIndexChanged(int index)
{
   for(int i=0;i<=14;i++)
   {
       qDebug()<<"index";
       if(index==i)
       {
           qDebug()<<i;
           QFont a;
           a.setPointSize(i+9);
           ui->messageBrowser->setCurrentFont(a);
           QString tmp_str=ui->messageBrowser->toPlainText();
           ui->messageBrowser->clear();
           ui->messageBrowser->setText(tmp_str);
       }
   }
}

void chat_room::changeddata(int a)
{
    qDebug()<<"changedata:"<<a;
    QString tmp="在线用户："+QString::number(a)+"人";
    ui->userNumLabel->setText(tmp);
}

void chat_room::read_to_close()
{
    QMessageBox::warning(0,"警告","服务器已经断开连接");
   // this->close();
}

void chat_room::closeEvent(QCloseEvent *)
{
    socket_com *s1=socket_com::getInstance();
    char closebuff[]="00000";
    send(s1->sockfd,closebuff,strlen(closebuff),0);
    ::close(s1->sockfd);
}
