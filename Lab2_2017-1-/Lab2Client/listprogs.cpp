#include "listprogs.h"
#include <QDebug>
#include <QString>
ListProgs::ListProgs(QWidget * parent):QListWidget(parent)
{

}

void ListProgs::addEl(QString name,QString id)
{
  qDebug()<<name <<"  ";
  MyItem* item= new MyItem(name,this);
  item->ID=id.toLongLong();
  addItem(item);
}

void ListProgs::delEl(QString name,QString id)
{
    QList<QListWidgetItem*> list=findItems(name, Qt::MatchFlag::MatchExactly);
    for(QListWidgetItem*i:list){
        if(dynamic_cast<MyItem*>(i)->ID==id.toLongLong()) takeItem(row(i));
    }
}

