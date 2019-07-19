#ifndef MYPROCESS_H
#define MYPROCESS_H
#include<QProcess>

class MyProcess:public QProcess
{
    Q_OBJECT
public:
    long long int ID;
    QString name;
    MyProcess(QObject *parent =nullptr);
};

#endif // MYPROCESS_H
