#ifndef REQIUST_H
#define REQIUST_H
#include<QString>

class reqiust
{
public:
    reqiust(QString message);
    QString getoPeration();
    QString getTime();
    QString getMes1();
    QString getMes2();
    QString getMes3();
    QString getMes4();
private:
    QString Message;
    QString operation;
    QString time;
    QString mes1;
    QString mes2;
    QString mes3;
    QString mes4;
    int index1,index2,index3,index4,index5;
};

#endif // REQIUST_H
