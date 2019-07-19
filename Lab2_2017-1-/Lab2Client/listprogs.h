#ifndef LISTPROGS_H
#define LISTPROGS_H
#include<QListWidget>


class MyItem:public QListWidgetItem
{
 public:
    long long int ID;
     MyItem(QListWidget*parent=nullptr):QListWidgetItem(parent){}
 MyItem(QString&text,QListWidget*parent=nullptr):QListWidgetItem(text,parent,Type){}

};

class ListProgs: public QListWidget
{
public:
    ListProgs(QWidget * parent=nullptr);
public slots:
    void addEl(QString name, QString id);
     void delEl(QString name, QString id);
};

#endif // LISTPROGS_H
