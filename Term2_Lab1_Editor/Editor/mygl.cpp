#include "mygl.h"
#include"GL/glu.h"

 MyGL::MyGL(QWidget* parent):QOpenGLWidget(parent)
{}

void MyGL::initializeGL()
{
   //initializeOpenGLFunctions();
    glClearColor(0.2,0.2,0.2,0.6);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
     glEnable(GL_LIGHTING|GL_AMBIENT|GL_DIFFUSE);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, lightDiffuse); //Setup The Diffuse Light
     glEnable(GL_LIGHTING|GL_AMBIENT|GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    ico->refine();
    ico->refine();
    ico->refine();
    ico->refine();
    ico->refine();
    ico->refine();
    ico->refine();


}


void MyGL::resizeGL(int w,int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(-w, -h, w, h);
    glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);


}

void MyGL::paintGL(){
    count++;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0,0.8,0.0);
    ico->draw();
   qDebug() << count;
}
