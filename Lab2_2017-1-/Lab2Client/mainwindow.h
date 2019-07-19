#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"my_socket.h"
#include"listprogs.h"
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
    void on_addProcess_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Socket *soc;
};

#endif // MAINWINDOW_H
