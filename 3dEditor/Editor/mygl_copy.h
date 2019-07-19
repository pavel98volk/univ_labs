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

#include "Figures/Ico.h"
#include "Figures/cone.h"
#include "Figures/cylinder.h"


class MyGL: public QOpenGLWidget
{
    Q_OBJECT
  public:
   explicit MyGL(QWidget *parent = 0);
   void initializeGL() override;
   void resizeGL(int w,int h) override;
   void paintGL() override;
   void keyPressEvent(QKeyEvent *event)override;
   void keyReleaseEvent(QKeyEvent*event)override;
   void mousePressEvent(QMouseEvent *event)override;
   void mouseReleaseEvent(QMouseEvent *event)override;
   void mouseMoveEvent(QMouseEvent *event)override;

   std::vector<Shape*> shapes;
 private:


public:
   unsigned int*checked = new unsigned int[1];//stencil
   int center_x,center_y;
   bool ctrl_pressed=false,shift_pressed=false,alt_pressed=false;//to determine if
   int x_pressed,y_pressed;//to count vector of mouse-move
private:
   GLfloat LightPosition[4]={0.0 ,0.0,200.0,1.0};
   GLfloat lightDiffuse[4] ={ 0.9f, 0.9f, 0.9f, 1.0f };
   GLfloat lightAmbient[4] ={ 0.1f, 0.1f, 0.1f, 1.0f };

public slots:
   void rotate_x(bool a);

};

#endif // MYGL_H
