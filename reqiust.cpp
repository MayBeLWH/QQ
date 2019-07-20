#include "reqiust.h"
#include<QDebug>
reqiust::reqiust(QString message):
    Message(message)
{
    index1=Message.indexOf("+");
    index2=Message.indexOf("+",index1+1);
    index3=Message.indexOf("+",index2+1);
    index4=Message.indexOf("+",index3+1);
    index5=Message.indexOf("+",index4+1);
    operation=Message.mid(0,index1);
    time=Message.mid(index1+1,index2-index1-1);
    mes1=Message.mid(index2+1,index3-index2-1);
    mes2=Message.mid(index3+1,index4-index3-1);
    mes3=Message.mid(index4+1,index5-index4-1);
    mes4=Message.mid(index5+1);
}//1+2342+24234+nfj

QString reqiust::getoPeration()
{
    return operation;
}

QString reqiust::getTime()
{
    return time;
}

QString reqiust::getMes1()
{
    return mes1;
}

QString reqiust::getMes2()
{
    return mes2;
}

QString reqiust::getMes3()
{
    return mes3;
}
QString reqiust::getMes4()
{
    return mes4;
}

