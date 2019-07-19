#include"my_socket.h"

Socket::Socket (QObject *parent): QObject(parent) {
    this->url=QUrl(QStringLiteral("ws://localhost:8080"));
    connect (&tcpSocket, &QTcpSocket::connected, this, &Socket::onConnected);
    connect (&tcpSocket, &QTcpSocket::disconnected, this, &Socket::closed);
    connect (&tcpSocket, &QTcpSocket::readyRead, this, &Socket::closed);
    tcpSocket.connectToHost("localhost",8080);
    if(!tcpSocket.waitForConnected(4000))
        qDebug() << "Error: " << tcpSocket.errorString();
    sendTextMessage("SHOW, ");
}

void Socket::onConnected () {
    qDebug()<< "connected";
    connect(&tcpSocket, &QTcpSocket::readyRead,this,&Socket::onTextMessage);
}


void Socket::onTextMessage () {

        QString data = tcpSocket.readAll();
        qDebug() <<data;
        QString operation=data.split(",").at(0);
        QString name =data.split(",").at(1);
        QString id= data.split(",").at(2);
        if(operation=="ADD")
        sendToList(name,id);
        if(operation=="REMOVE")
        deleteFromList(name,id);
}
void Socket::sendTextMessage (QString message ) {
    tcpSocket.write(message.toLatin1());
}


