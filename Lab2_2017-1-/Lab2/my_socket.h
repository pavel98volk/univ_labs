#ifndef MY_SOCKET_H
#define MY_SOCKET_H

#include <QtWebSockets/QWebSocket>
#include"QTcpSocket"
class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr);
    void sendTextMessage(QString message);
public slots:
     void onConnected();
    void onTextMessage();
signals:
    void closed();
private:
    QTcpSocket tcpSocket;
    QUrl url;
};
#endif // MY_SOCKET_H
