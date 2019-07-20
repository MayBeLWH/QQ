#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include<datebase.h>
#include<QList>

namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();
private:
    void sendString(QString );
private slots:
    void server_New_Connect();
    void socket_Read_Data();
//       void socket_Disconnected();
private:
    Ui::Server *ui;
    QTcpServer * server;
    QList<QTcpSocket*> *socket_list;
    dateBase *mydate;
    QString Operation;
    QString Time;
    QString mes1;
    QString mes2;
    QString mes3;
    QString mes4;
    void addAction(QString);
};

#endif // SERVER_H
