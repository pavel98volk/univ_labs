#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->openGLWidget->addSphere(true);
}

void MainWindow::on_pushButton_3_clicked()
{
     ui->openGLWidget->addCylinder(true);
}

void MainWindow::on_pushButton_2_clicked()
{
      ui->openGLWidget->addCone(true);
}
