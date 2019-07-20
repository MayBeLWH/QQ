#include "server.h"
#include "ui_server.h"
#include<reqiust.h>

Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    server = new QTcpServer(this);
    socket_list=new QList<QTcpSocket*>;
    mydate=new dateBase();
    mydate->createConnection();
    if(!server->listen(QHostAddress::Any,6666))
    {
        // 监视本地主机的6666端口，如果出错就输出错误信息，并关闭
        qDebug() << server->errorString();
//        close();
    }
    //连接
    connect(server,SIGNAL(newConnection()),this, SLOT(server_New_Connect()));
}

Server::~Server()
{
    server->close();
    server->deleteLater();
    delete ui;
}

void Server::sendString(QString mes)
{
    // 用于暂存我们要发送的数据
    QByteArray block;
    // 使用数据流写入数据
    QDataStream out(&block,QIODevice::WriteOnly);
    //使用数据流写入数据
    out.setVersion(QDataStream::Qt_4_6);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out<<(quint16) 0;
    out<<mes;
    qDebug()<<mes;
    out.device()->seek(0);
    out<<(quint16)(block.size()-sizeof(quint16));
    for(int i=0;i<socket_list->length();i++)
        socket_list->at(i)->write(block);
}

void Server::server_New_Connect()
{
    //获取客户端连接
    QTcpSocket *socket =new QTcpSocket();
    socket = server->nextPendingConnection();
    qDebug() << "new user connected!";
    socket_list->append(socket);
    qDebug()<<socket_list->length();
    //连接QTcpSocket的信号槽，以读取新数据
    QObject::connect(socket, SIGNAL(readyRead()),this,SLOT(socket_Read_Data()));
    QObject::connect(socket, &QTcpSocket::disconnected,this,[=](){
        socket_list->removeOne(socket);
        delete socket;
    } );
}

void Server::socket_Read_Data()
{
    QByteArray buffer;
    //读取缓冲区数据
    for(int i=0;i<socket_list->length();i++){
        buffer.clear();
        buffer = socket_list->at(i)->readAll();
        if(!buffer.isEmpty())
        {
            QString str = tr(buffer);
            qDebug()<< str;
            reqiust* requist=new reqiust(str);
            Operation=requist->getoPeration();
            Time=requist->getTime();
            mes1=requist->getMes1();
            mes2=requist->getMes2();
            mes3=requist->getMes3();
            mes4=requist->getMes4();
            if(Operation=="01"){
                if(mydate->Login(mes1,mes2)){
                    sendString("01+1+"+mes1);
                    addAction(mes1+" 登入成功");
                }
                else{
                    sendString("01+0+"+mes1);
                    addAction(mes1+" 登入失败");
                }
            }
            else if(Operation=="00"){
                if(mydate->isUser(mes1)){
                    sendString("00+0+"+mes1);
                    addAction(mes1+" 注册失败");
                }else {
                    mydate->addUser(mes1,mes2,mes3);
                    mydate->createTable(mes1);
                    sendString("00+1+"+mes1);
                    addAction(mes1+"注册成功并在数据库中创建好友列表");
                }
            }
            else if(Operation=="02"){
                //对应修改密码
                if(mydate->isUser(mes1)){
                    mydate->changePas(mes1,mes2);
                    sendString("02+1+"+mes1);
                    addAction(mes1 +" 修改密码成功");
                }else {
                    sendString("02+0+"+mes1);
                    addAction(mes1+" 修改密码失败");
                }
            }
            else if(Operation=="03"){
                if(mydate->isUser(mes1)){
                    sendString("03+"+Time+"+1+"+mes1+"+"+mydate->getFriends(mes1));
                    addAction(mes1+" 请求刷新好友列表成功");
                }else{
                    sendString("03+0+"+mes1);
                    addAction(mes1+" 请求刷新好友列表失败");
                }
            }
            else if(Operation=="04"){
//            "04+18:30:10+"+account
                if(mydate->isUser(mes1)){
                    sendString("04+"+Time+"+1+"+mes1+"+"+mydate->getChats(mes1));
                    addAction(mes1+" 请求刷新聊天记录成功");
                }else {
                    sendString("04+"+Time+"+0+"+mes1);
                    addAction(mes1+" 请求刷新聊天记录失败");
                }
            }
            else if(Operation=="05"){
//                "05+"+Time+"+"+account+"+"+friendAcco+"+"+friendNickname+"+"+friendPart
                if(mydate->isUser(mes2)){
                    if(mydate->isMyFriend(mes1,mes2)){
                        sendString("05+"+Time+"+2+"+mes1);
                        addAction(mes1+" 请求加"+mes2+"为好友失败，已加");
                    }else {
                        mydate->addFriend(mes1,mes2,mes3,mes4);
                        mydate->addChat(mes1,mes2,Time,"#&<");
                        sendString("05+"+Time+"+1+"+mes1);
                        sendString("04+"+Time+"+1+"+mes2+"+"+mydate->getChats(mes2));
                        //12表示有人要加你为好友
                        addAction(mes1+" 请求加"+mes2+"为好友成功，发送好友请求");
                    }
                }
                else{
                   sendString("05+"+Time+"+0+"+mes1);
                    addAction(mes1+" 请求加"+mes2+"为好友失败，用户不存在");
                }
            }
            else if(Operation=="06"){
                //"06+18:30:10+"+account+"+"+friend_account
                qDebug()<<mes1;
                qDebug()<<mes2;
                if((mydate->isUser(mes1))&&(mydate->isUser(mes2))){
                    sendString("06+"+Time+"+1+"+mes1+"+"+mydate->getOurChats(mes1,mes2));
                     addAction(mes1+" 请求刷新与"+mes2+"的聊天界面成功");
                }
                else {
                   sendString("06+"+Time+"+0+"+mes1);
                     addAction(mes1+" 请求刷新与"+mes2+"的聊天界面失败");
                }
            }
            else if(Operation=="07"){
                if(mydate->isUser(mes1)&&mydate->isUser(mes2)){
                    if(mydate->isAvaiable(mes2,mes1)){
                        mydate->addChat(mes1,mes2,Time,mes3);
                        sendString("06+"+Time+"+1+"+mes2+"+"+mydate->getOurChats(mes2,mes1));
                        addAction(mes1+" 请求发送给"+mes2+"一条消息："+mes3+"成功");
                    }
                }
                else {
                   sendString("07+"+Time+"+0+"+mes1);
                   addAction(mes1+" 请求发送给"+mes2+"一条消息："+mes3+"失败");
                }
            }
            else if(Operation=="09"){
                //"09+"+getNowTime()+"+"+account+"+"+friend_account
                if(mydate->isUser(mes1)&&mydate->isUser(mes2)){
                    mydate->blackFriend(mes1,mes2);
                    if(mydate->isAvaiable(mes1,mes2)){
                        sendString("09+"+Time+"+1+"+mes1+"+0");
                        addAction(mes1+" 请求与 "+mes2+" 回复通信成功");
                    }else{
                        sendString("09+"+Time+"+1+"+mes1+"+1");
                        addAction(mes1+" 请求拉黑 "+mes2+" 成功");

                    }
                }else{
                    if(mydate->isAvaiable(mes1,mes2)){
                        sendString("09+"+Time+"+0+"+mes1+"+1");
                        addAction(mes1+" 请求拉黑 "+mes2+" 失败");
                    }else{
                        sendString("09+"+Time+"+0+"+mes1+"+0");
                        addAction(mes1+" 请求与 "+mes2+" 回复通信失败");
                    }
                }
            }
            else if(Operation=="10"){
                 if(mydate->isUser(mes1)&&mydate->isUser(mes2)){
                     mydate->daleteFriend(mes1,mes2);
                     mydate->daleteFriend(mes1,mes2);
                     sendString("10+"+Time+"+1+"+mes1);
                     addAction(mes1+" 请求删除好友 "+mes2+" 成功");
                 }
                 else{
                     sendString("10+"+Time+"+0+"+mes1);
                     addAction(mes1+" 请求删除好友 "+mes2+" 失败");
                 }
            }
            else if(Operation=="12"){
                //"12+"+getNowTime()+"+"+account+"+"+friendAcco+"+"+friendNickname+"+"+friendPart
                mydate->agreeAddFriend(mes2,mes1);
                mydate->addFriend(mes1,mes2,mes3,mes4);
                mydate->agreeAddFriend(mes1,mes2);
                mydate->deleteChat(mes1);
                sendString("12+"+Time+"+1+"+mes2+"+"+mes1);
                addAction(mes1+" 同意加好友 "+mes2+" 成功");
            }
            else if(Operation=="13"){
                mydate->daleteFriend(mes2,mes1);
                mydate->deleteChat(mes1);
                sendString("12+"+Time+"+0+"+mes2+"+"+mes1);
                addAction(mes1+" 拒绝加好友 "+mes2+" 成功");
            }
            else if(Operation=="14"){
                //"14+"+getNowTime()+"+"+account+"+"+friend_account+"+"+nick
                mydate->changeNick(mes1,mes2,mes3);
            }
            else if(Operation=="15"){
                //"14+"+getNowTime()+"+"+account+"+"+friend_account+"+"+nick
                mydate->changePart(mes1,mes2,mes3);
            }
        }
    }

}

void Server::addAction(QString s1)
{
  ui->textBrowser->append(s1);
}
//void Server::socket_Disconnected()
//{
//    qDebug() << "Disconnected!";
//}
