#include "mygl.h"
#include"GL/glu.h"

 MyGL::MyGL(QWidget* parent):QOpenGLWidget(parent)
{
     shapes.push_back((new Ico(40)));
     shapes.push_back((new Ico(40)));
     shapes[1]->set_translation(-70,0,-100);


setFocus();

 }

 void MyGL::perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
 {
     GLdouble xmin, xmax, ymin, ymax;

     ymax = zNear * tan( fovy * M_PI / 360.0 );
     ymin = -ymax;
     xmin = ymin * aspect;
     xmax = ymax * aspect;

     glFrustum( xmin, xmax, ymin, ymax, zNear, zFar );
 }
void MyGL::initializeGL()
{
    glClearColor(0.2,0.2,0.2,0.6);

    glLoadIdentity();
 glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
   glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0,GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0,GL_POSITION,LightPosition);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glMatrixMode(GL_PROJECTION);
    perspective(90.0,1,1.0,100);
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0,0,-5);


}

void MyGL::resizeGL(int w,int h){
    center_x=w/2,center_y=h/2;
    glViewport(-w, -h, w, h);
   glOrtho(-w/10, w/10, -h/10, h/10, -100.0f, 100.0f);
  //gluPerspective(45.0,w/h,0.1,100.0);
  // glFrustum(1, 1, 1, 1, 1.0f, 10.0f);
    glMatrixMode(GL_PROJECTION);
}

void MyGL::paintGL(){



  // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

   // glReadPixels(x_pressed,y_pressed,1,1,GL_STENCIL_INDEX,GL_UNSIGNED_BYTE,checked);
   // qDebug()<<"\n"<<checked[0]<<"\n";

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glClearStencil(100);
    glClear(GL_STENCIL_BUFFER_BIT);

    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
    glColor3f(0.8,0.2,0.6);
    for(int i=0;i<shapes.size();i++){
        glStencilFunc(GL_ALWAYS,i,i);
        shapes[i]->draw_gl();
    }




}

void MyGL::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Control:
         ctrl_pressed=true;
        break;
    case Qt::Key_Shift:
        shift_pressed=true;
        break;
    case Qt::Key_Alt:
         alt_pressed=true;
         break;
     case Qt::Key_Up:
        z_pressed=true;
         break;
    case Qt::Key_Down:
        color_pressed=true;
         break;

    }
}
void MyGL::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Control:
         ctrl_pressed=false;
         break;
    case Qt::Key_Shift:
        shift_pressed=false;
        break;
    case Qt::Key_Alt:
        alt_pressed=false;
        break;
    case Qt::Key_Up:
       z_pressed=false;
        break;
   case Qt::Key_Down:
       color_pressed=false;
        break;
    }
}


//MOUSE

void MyGL::mousePressEvent(QMouseEvent *event)
{
    makeCurrent();
    x_pressed=event->pos().x();
    y_pressed=event->pos().y();
    checked[0] = 1;
    glReadPixels(x_pressed,2*center_y -y_pressed-1,1,1,GL_STENCIL_INDEX,GL_UNSIGNED_BYTE,checked);
    qDebug()<<checked[0];


}
void MyGL::mouseReleaseEvent(QMouseEvent *event)
{
   shapes[checked[0]]->add_rotations();
   shapes[checked[0]]->add_translations();
   shapes[checked[0]]->add_scale();

}

void MyGL::mouseMoveEvent(QMouseEvent *event)
{
    //pressing z should replace x axis with z;
    if(checked[0]==100) return;
    if(ctrl_pressed)
      shapes[checked[0]]->set_temp_translation((event->pos().x()-x_pressed)/3,(y_pressed-event->pos().y())/3,0);
    else if(shift_pressed)
      shapes[checked[0]]->set_temp_rotation(-(y_pressed-event->pos().y())/5 ,(event->pos().x()-x_pressed)/5,0);
    else if(alt_pressed){
        shapes[checked[0]]->set_temp_scale((y_pressed-event->pos().y())/100.0,(event->pos().x()-x_pressed)/100.0,0);
    }
    else if(z_pressed){
        shapes[checked[0]]->set_temp_translation(0 ,0,(event->pos().x()-x_pressed)/3+(y_pressed-event->pos().y())/3);
    }
    else if(color_pressed){
        shapes[checked[0]]->color[0] =((event->pos().x()-x_pressed)/10+(y_pressed-event->pos().y())/10) %255;
        shapes[checked[0]]->color[1] =((event->pos().x()-x_pressed)/10-(y_pressed-event->pos().y())/10) %255;
        shapes[checked[0]]->color[1] =(-(event->pos().x()-x_pressed)/10+(y_pressed-event->pos().y())/10) %255;
    }
  //  else if(z_pressed)

     update();

}

void MyGL::addSphere(bool a){
    shapes.push_back(new Ico(40));
    setFocus();
    update();
}
void MyGL::addCone(bool a){
    shapes.push_back(new Cone(30,60));
    setFocus();
    update();
}
void MyGL::addCylinder(bool a){
    shapes.push_back(new Cylinder(30,60));
    setFocus();
    update();
}

