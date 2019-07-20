#include "datebase.h"


dateBase::dateBase()
{

}
//建立一个数据库连接
bool dateBase::createConnection()
{
    //以后就可以用"sqlite1"与数据库进行连接了
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "sqlite1");
    db.setDatabaseName(".//QQ.db");
    if( !db.open())
    {
        qDebug() << "无法建立数据库连接";
        return false;
    }
    return true;
}
//创建数据库表
bool dateBase::createTable(QString acot)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
//    QString order1="drop table 你想干那friend";
//    QString order2="drop table friend2";
    QString order="create table friend"+acot+" (account varchar(10), username varchar(10), nickname varchar(10),fenzu varchar(10),isAvaiable varchar(10))";
//    QString order="create table Chats (sender  varchar(10),receiver  varchar(10),timer varchar(10),conclude varchar(100))";&&query.exec(order2)
    bool success = query.exec(order);
    if(success)
    {
        qDebug() << QObject::tr("好友列表创建成功！\n");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("好友列表创建失败！\n");
        return false;
    }
    db.close();
}

bool dateBase::addUser(QString account, QString name, QString password)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="insert into user values (\""+account+"\",\""+name+"\",\""+password+"\")";
    bool success = query.exec(order);
    if(success)
    {
        qDebug() << QObject::tr("加入用户成功！\n");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("加入用户失败！\n");
        return false;
    }
    db.close();
}
//account int primary key,name varchar(10),password int
bool dateBase::isUser(QString acoun)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="select account from user";
    bool success = query.exec(order);
    if(success)
    {
        qDebug() << QObject::tr("查询操作成功！\n");
        while(query.next()){
           if(acoun==query.value(0).toString()){
                return true;
           }
        }
        return false;
    }
    else
    {
        qDebug() << QObject::tr("查询操作失败！\n");
    }
    db.close();
}

bool dateBase::Login(QString acco, QString pass)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="select account, password from user";
    bool success = query.exec(order);
    if(success)
    {
        qDebug() << QObject::tr("查询操作成功！\n");
        while(query.next()){
           if(acco==query.value(0).toString()&&pass==query.value(1).toString()){
                return true;
           }
        }
        return false;
    }
    else
    {
        qDebug() << QObject::tr("查询操作失败！\n");
    }
    db.close();
}

QString dateBase::getFriends(QString aco)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="select fenzu, account, nickname ,isAvaiable  from friend"+aco;
    bool success = query.exec(order);
    if(success)
    {
        QString friends;
        qDebug() << QObject::tr("查询操作成功！\n");
        while(query.next()){
            if(query.value(3).toString()!="2"){
                 friends+=query.value(0).toString()+","+query.value(1).toString()+","+query.value(2).toString()+";";
            }
        }
        return friends;
    }
    else
    {
        qDebug() << QObject::tr("查询操作失败！\n");
    }
    db.close();
}

bool dateBase::isMyFriend(QString user, QString frien)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="select account  from friend"+user;
     bool success = query.exec(order);
     if(success)
     {
         qDebug() << QObject::tr("查询是否好友操作成功！\n");
         while(query.next()){
               if(query.value(0).toString()==frien){
                   return true;
               }
         }
         return false;
     }
     else
     {
         qDebug() << QObject::tr("查询是否好友操作失败！\n");
     }
     db.close();
}

bool dateBase::addFriend(QString user, QString newFried, QString nickname, QString fenzu)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString istrue="2";
    QString username;
    QString order1="select account,name from users ";
    query.exec(order1);
    while(query.next()){
          if(query.value(0).toString()==newFried){
              username==query.value(1).toString();
          }
    }
    QString order="insert into friend"+user+" values (\""+newFried+"\",\""+username+"\",\""+nickname+"\",\""+fenzu+"\",\""+istrue+"\")";
     bool success = query.exec(order);
     if(success)
     {
         qDebug() << QObject::tr("查询是否好友操作成功！\n");
         return true;
     }
     else
     {
         qDebug() << QObject::tr("查询是否好友操作失败！\n");
         return false;
     }
     db.close();
}

bool dateBase::agreeAddFriend (QString user, QString frid)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="update friend"+user+" set isAvaiable=\"1\" where account = "+frid;
    qDebug()<<order;
     bool success = query.exec(order);
     if(success)
     {
         qDebug() << QObject::tr("同意加好友操作成功！\n");
         return true;
     }
     else
     {
         qDebug() << QObject::tr("同意加好友操作失败！\n");
         return false;
     }
     db.close();
}

bool dateBase::blackFriend(QString user, QString frien)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec("select account, isAvaiable from friend"+user);
    QString isAvaiable;
    while(query.next()){
        if(frien==query.value(0).toString()){
            isAvaiable=query.value(1).toString();
        }
    }
    QString order;
    if(isAvaiable=="1")
        order="update friend"+user+" set isAvaiable=\"0\" where account="+frien;
    else if (isAvaiable=="0")
        order="update friend"+user+" set isAvaiable=\"1\" where account="+frien;
    bool success = query.exec(order);
    if(success)
    {
        qDebug() << QObject::tr("拉黑操作成功！\n");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("拉黑好友操作失败！\n");
        return false;
    }
    db.close();
}

bool dateBase::daleteFriend(QString user, QString frien)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="delete from friend"+user+" where account="+frien;
//    QString order="delete from Chats";
    bool success=query.exec(order);
    if(success)
    {
        qDebug() << QObject::tr("删除好友操作成功！\n");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("删除好友操作失败！\n");
        return false;
    }
    db.close();
}
bool dateBase::isAvaiable(QString user,QString fried){
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
//    select sender,receiver,timer,conclude from Chats
    QString order="select account,isAvaiable from friend"+user;
    bool success=query.exec(order);
    if(success)
    {
        qDebug() << QObject::tr("查询好友是否拉黑操作成功！\n");
        while(query.next()){
            if(query.value(0).toString()==fried&&query.value(1).toString()=="1"){
                return true;
            }
            if(query.value(0).toString()==fried&&query.value(1).toString()=="0"){
                return false;
            }
        }
    }
    else
    {
        qDebug() << QObject::tr("查询好友是否拉黑操作失败！\n");
        return false;
    }
    db.close();
}

bool dateBase::deleteChat(QString user)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="delete from Chats where conclude=\"#&<\" and receiver="+user;
    bool success=query.exec(order);
    if(success)
    {
        qDebug() << QObject::tr("删除加好友记录插入成功！\n");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("删除加好友记录插入失败！\n");
        return false;
    }
    db.close();
}

bool dateBase::changePart(QString user, QString frid, QString fenzu)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="update friend"+user+" set fenzu = \""+fenzu+"\" where account = \""+frid+"\"";
    bool success=query.exec(order);
    if(success)
    {
        return true;
        qDebug() << QObject::tr("修改好友分组成功\n");
    }
    else
    {
         return false;
        qDebug() << QObject::tr("修改好友分组失败\n");
    }
    db.close();
}

bool dateBase::changeNick(QString user, QString frid, QString nick)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="update friend"+user+" set nickname = \""+nick+"\" where account = \""+frid+"\"";
    bool success=query.exec(order);
    if(success)
    {
        return true;
        qDebug() << QObject::tr("修改好友昵称成功\n");
    }
    else
    {
         return false;
        qDebug() << QObject::tr("修改好友昵称失败\n");
    }
    db.close();
}

bool dateBase::addChat(QString sender, QString receiver, QString timer, QString couclude)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="insert into Chats values (\""+sender+"\",\""+receiver+"\",\""+timer+"\",\""+couclude+"\")";
    bool success=query.exec(order);
    if(success)
    {
        qDebug() << QObject::tr("聊天记录插入成功！\n");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("聊天记录插入失败！\n");
        return false;
    }
    db.close();
}

bool dateBase::daleteChat(QString user1, QString user2)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="delete from Chats where sender="+user1+" and receiver="+user2;
    QString order1="delete from Chats where sender="+user2+" and receiver="+user1;
    bool success=query.exec(order)&&query.exec(order1);
    if(success)
    {
        qDebug() << QObject::tr("删除两个好友之间的记录成功！\n");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("删除两个好友之间的记录失败！\n");
        return false;
    }
    db.close();
}

QString dateBase::getChats(QString user)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="select sender,receiver,timer,conclude from Chats";
    bool success=query.exec(order);
    if(success)
    {
        QString chats;
        while(query.next()){
            if((query.value(0).toString()==user)||(query.value(1).toString()==user))
                chats+=query.value(0).toString()+"|"+query.value(1).toString()+"|"+query.value(2).toString()+"|"+query.value(3).toString()+";";
        }
        return chats;
        qDebug() << QObject::tr("获取单个用户聊天记录成功！\n");
    }
    else
    {
        qDebug() << QObject::tr("获取单个用户聊天记录失败！\n");
    }
    db.close();
}

QString dateBase::getOurChats(QString user, QString fried)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="select sender,receiver,timer,conclude from Chats";
    bool success=query.exec(order);
    if(success)
    {
        QString chats;
        while(query.next()){
            if((query.value(0)==user&&query.value(1)==fried)||(query.value(0)==fried&&query.value(1)==user))
                chats+=query.value(0).toString()+"|"+query.value(1).toString()+"|"+query.value(2).toString()+"|"+query.value(3).toString()+";";
        }
        return chats;
        qDebug() << QObject::tr("获取两个用户之间聊天记录成功！\n");
    }
    else
    {
        qDebug() << QObject::tr("获取两个用户之间聊天记录失败！\n");
    }
    db.close();
}

bool dateBase::changePas(QString use, QString pas)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString order="update user set password = \""+pas+"\" where account = \""+use+"\"";
    bool success=query.exec(order);
    if(success)
    {
        return true;
        qDebug() << QObject::tr("修改密码成功\n");
    }
    else
    {
         return false;
        qDebug() << QObject::tr("修改密码失败\n");
    }
    db.close();
}
