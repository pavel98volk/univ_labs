#ifndef MYGL_H
#define MYGL_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <vector>
#include <list>
#include "field.h"

class MyGL: public QOpenGLWidget
{
    Q_OBJECT
  public:
   explicit MyGL(QWidget *parent = 0);
   void initializeGL() override;
   void resizeGL(int w,int h) override;
   void paintGL() override;
   void mousePressEvent(QMouseEvent *event)override;
   void mouseReleaseEvent(QMouseEvent *event)override;
   void mouseMoveEvent(QMouseEvent *event)override;

 private:
   // void resetGame();
    void drawField();
    void drawCheckers();
    void drawChecker();
    void drawGod();
    void drawCircleEm();
    void drawCellsEm();
    void drawPhantom();

public:
int x_pressed,y_pressed;
int width,height;
int w8,h8;
///////
Field *field = nullptr;  // 'b'-blue 'r' - red ' '-' -none
int *circ_em = nullptr;
QList<int*>*cell_em = nullptr;
int phantomPos[2]={-1,-1};

private:

public slots:
void drawGame(QList<int*>& cells_em,Field& field,int *ch_em,int phantomx=-1,int phantomy=-1);

signals:
 void clicked(int x, int y);
};

#endif // MYGL_H
