#include "server.h"
#include <QApplication>
#include<datebase.h>
#include<QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QTime timer=QTime::currentTime();
//    int hour=timer.hour();
//    int minter=timer.minute();
//    int seond=timer.second();
//    qDebug()<< QString::number(hour)+":"+QString::number(minter)+":"+QString::number(seond);
    Server w;
    w.show();
//    dateBase d;
//    d.createConnection();
//    d.daleteFriend("","");
//    d.addChat("1","2","09:54:33","hello! I want to make friends with you.");
//    d.addFriend("1","2","1","baby","family");
//    d.addFriend("2","1","2","baby","family");
//    d.addUser("","" ,"");
//    d.createTable("1");
//    d.createTable("2");
//    d.createTable("你想干那");
//    d.addUser("1","2","3");
//    if(d.Login("1","3"))
//      qDebug()<<"在";
//    else
//         qDebug()<<"不在";
//    if(d.Login("1","2"))
//      qDebug()<<"在";
//    else
//         qDebug()<<"不在";
    return a.exec();
}
