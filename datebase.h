#ifndef DATEBASE_H
#define DATEBASE_H

#include <QDebug>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include<QString>
//将数据库的基本操作封装在本类中，只向外暴露一些基本的功能函数
class dateBase
{
public:
    dateBase();
    bool createConnection();                                               //创建一个连接
    bool createTable(QString);                                            //创建数据库表
    bool addUser(QString,QString,QString);                        //增加用户
    bool isUser(QString);                                                    //检测用户是否在数据库中
    bool Login(QString,QString);                                        //登入时检测账户与密码是否匹配
    QString getFriends(QString);                                        //获取该账户的好友列表
    bool isMyFriend(QString,QString);                                //判断账户是不是自己好友
    bool addFriend(QString,QString,QString,QString);        //加好友
    bool agreeAddFriend(QString,QString);                         //同意加好友
    bool blackFriend(QString,QString);                              //拉黑好友
    bool daleteFriend(QString,QString);                             //删除好友
    bool addChat(QString,QString,QString,QString);          //增加聊天记录
    bool daleteChat(QString,QString);                               //删除指定好友间的聊天信息
    QString getChats(QString);                                          //获取用户的聊天记录
    QString getOurChats(QString,QString);                       //获取用户的聊天记录
    bool changePas(QString,QString);                                //用户修改密码
    bool isAvaiable(QString,QString);                                //检查好友是否拉黑
    bool deleteChat(QString);                                            //删除加好友指定的信息
    bool changePart(QString,QString,QString);                 //修改好友到指定分组
    bool changeNick(QString,QString,QString);                //修改好友昵称
};

#endif // DATEBASE_H
