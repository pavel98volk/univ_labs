#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mygl.h"
#include"game.h"
#include<QObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_newButton_clicked();

private:
    Ui::MainWindow *ui;
    Game game;
};

#endif // MAINWINDOW_H
