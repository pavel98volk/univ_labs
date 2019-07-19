#include"server.h"
#include<string>
#include <windows.h>
#include <wchar.h>
#include <QtCore>

Server::Server(quint16 port,  QObject *parent):
    QObject(parent)
    ,TcpServer(new QTcpServer(this))
{
    qDebug() << ">Your local directory: use relative or absolute path: "<< QCoreApplication::applicationDirPath();// /// / / / / /
  if (TcpServer->listen(QHostAddress::Any, port)) {
          qDebug() << "TCP listening on port" << port;
      connect(TcpServer, &QTcpServer::newConnection,this, &Server::clientConnected);
   }


}
Server::~Server(){
     for(QTcpSocket* client:tcp_clients){
        delete client;
     }
     for(MyProcess*i :process_list){
         i->terminate();
         delete i;
     }
}

void Server::progClosed(int ExitCode)
{
    qDebug()<<"closed";
    MyProcess* proc = dynamic_cast<MyProcess*>(sender());
    for(MyProcess*i : process_list){
      if(i->ID==proc->ID){
          for(QTcpSocket* client:tcp_clients){
              client->write("REMOVE,"+proc->name.toLatin1()+","+QString::number(proc->ID).toLatin1());
          }
          i->deleteLater();process_list.removeOne(i);
      }
    }
}

void Server::progOpened()
{
    qDebug()<<"opened";
    MyProcess* proc = dynamic_cast<MyProcess*>(sender());
    proc->ID=proc->processId();
     for(QTcpSocket* client:tcp_clients)client->write("ADD,"+proc->name.toLatin1()+","+QString::number(proc->ID).toLatin1());
}



bool Server::addProcess(QTcpSocket *client, QString name)
{
 MyProcess *proc = new MyProcess(this);
 proc->name=name;
 connect(proc,static_cast<void(MyProcess::*)(int, MyProcess::ExitStatus)>(&MyProcess::finished),this,&Server::progClosed);
 connect(proc,&MyProcess::started, this,&Server::progOpened);
  process_list.push_back(proc);
 proc->start(name);
}

void Server::giveProcessList(QTcpSocket *client)
{
    qDebug()<< "shown";
    for(MyProcess*i : process_list){
        qDebug()<< "shown";
        client->write("ADD,"+i->name.toLatin1()+","+QString::number(i->ID).toLatin1());
    }
}

void Server::closeProg(QString procId)
{
    for(MyProcess*i : process_list){
        if(i->processId() == procId.toLongLong()){
            for(QTcpSocket* client:tcp_clients)client->write("REMOVE,"+i->name.toLatin1()+","+QString::number(i->ID).toLatin1());
            process_list.removeOne(i);
            i->close();
            i->deleteLater();
        }
    }
}




void Server::clientConnected(){
    qDebug()<<"connected";
    QTcpSocket* tcp_client = TcpServer->nextPendingConnection();
    connect(tcp_client, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcp_client,&QTcpSocket::disconnected,this, &Server::clientDisconnected);
    tcp_clients<<tcp_client;

}

void Server::readMessage(){
QTcpSocket* client=qobject_cast<QTcpSocket*>(sender());
    QString data = client->readAll();
    QString operation =data.split(",").at(0);
    data =data.split(",").at(1);
    if(operation=="START")
    addProcess(client,data);
    else if(operation=="SHOW")
    giveProcessList(client);
    else if(operation=="STOP")
    closeProg(data);
}


void Server::clientDisconnected(){
     QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
     if(client){
    tcp_clients.removeOne(client);
     client->deleteLater();
     }
}
