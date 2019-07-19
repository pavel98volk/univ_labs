#include <QCoreApplication>
#include"server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server *server = new Server(8080,nullptr);
   // QObject::connect(server, &EchoServer::closed, &a, &QCoreApplication::quit);
    return a.exec();
}
