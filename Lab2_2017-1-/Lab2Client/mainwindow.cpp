#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->soc = new Socket(this);
    ui->setupUi(this);
    connect(soc,Socket::sendToList,ui->listWidget,ListProgs::addEl);
    connect(soc,Socket::deleteFromList,ui->listWidget,ListProgs::delEl);
    soc->sendTextMessage("GET, ");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addProcess_clicked()
{
    soc->sendTextMessage("START,\""+ui->processName->text()+"\"");
    ui->processName->clear();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
      MyItem* it=dynamic_cast<MyItem*>(item);
      soc->sendTextMessage("STOP,"+QString::number(it->ID).toLatin1());
}
