#include"my_socket.h"

Socket::Socket (QObject *parent): QObject(parent) {
    this->url=QUrl(QStringLiteral("ws://localhost:8080"));
    connect (&tcpSocket, &QTcpSocket::connected, this, &Socket::onConnected);
    connect (&tcpSocket, &QTcpSocket::disconnected, this, &Socket::closed);
    tcpSocket.connectToHost("localhost",8080);
    if(!tcpSocket.waitForConnected(4000))
        qDebug() << "Error: " << tcpSocket.errorString();
}

void Socket::onConnected () {
    qDebug()<< "connected";
    connect(&tcpSocket, &QTcpSocket::readyRead,this,&Socket::onTextMessage);
}

void Socket::onTextMessage () {
 qDebug() << tcpSocket.readAll();
}
void Socket::sendTextMessage (QString message ) {
   tcpSocket.write(message.toLatin1());
}
