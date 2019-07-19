#ifndef SERVER_H
#define SERVER_H

#include <QList>
#include<QObject>


#include "QTcpServer"
#include "QTcpSocket"
#include <QDebug>
#include <QProcess>

#include <QtCore/QByteArray>
#include <QProcess>
#include"myprocess.h"



class Server:public QObject{
    Q_OBJECT
private:

    QTcpServer *TcpServer;
    QList<QTcpSocket *>tcp_clients;
    QList<MyProcess *>process_list;
public:
   explicit Server(quint16 port,  QObject *parent = nullptr);
    ~Server();
private:
    bool addProcess(QTcpSocket *client,QString name);
    void giveProcessList(QTcpSocket*client);
    void closeProg(QString procId );

Q_SIGNALS:
    void closed();
private slots:
   void progClosed(int ExitCode);
   void progOpened();
   void clientConnected();
   void clientDisconnected();
   void readMessage();
};



#endif // SERVER_H
