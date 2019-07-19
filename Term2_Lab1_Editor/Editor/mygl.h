#ifndef MYGL_H
#define MYGL_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QDebug>
#include "Figures/Ico.h"

class MyGL: public QOpenGLWidget
{
    Q_OBJECT
  public:
   explicit MyGL(QWidget *parent = 0);
   void initializeGL() override;
   void resizeGL(int w,int h) override;
   void paintGL() override;

public:
   Ico* ico = new Ico(15);
   int count=0;

private:
   float lightDiffuse[4] ={ 0.2f, 0.3f, 0.6f, 1.0f };

};

#endif // MYGL_H
