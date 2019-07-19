#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    game.setParent(this);
    ui->setupUi(this);
    connect(&game,&Game::drawField,ui->myGL,&MyGL::drawGame);
    connect(ui->myGL,MyGL::clicked,&game,&Game::clicked);
    game.start(false,false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newButton_clicked()
{
    this->game.restart();
}
