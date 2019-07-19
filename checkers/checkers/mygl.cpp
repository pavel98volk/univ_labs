#include "mygl.h"
#include"GL/glu.h"

 MyGL::MyGL(QWidget* parent):QOpenGLWidget(parent)
{
width=height=h8=w8=0;
setFocus();
 }

void MyGL::initializeGL()
{
    glClearColor(0.7,0.4,0.15,0.8);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_NORMALIZE);

}

void MyGL::resizeGL(int w,int h){
    width=w;
    height=h;
    h8=(height+4)/8;
    w8=(width+4)/8;
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, w, h);
   glOrtho(0, w, 0, h,-10,10);
}

void MyGL::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT);
    drawField();
     drawCellsEm();
       drawPhantom();
    drawCheckers();
    drawCircleEm();


  //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

   // glReadPixels(x_pressed,y_pressed,1,1,GL_STENCIL_INDEX,GL_UNSIGNED_BYTE,checked);






}




//MOUSE

void MyGL::mousePressEvent(QMouseEvent *event)
{
    makeCurrent();
    x_pressed=event->pos().x();
    y_pressed=event->pos().y();
    clicked(x_pressed/w8,7-y_pressed/h8);


}
void MyGL::mouseReleaseEvent(QMouseEvent *event)
{

}

void MyGL::mouseMoveEvent(QMouseEvent *event)
{

}
//////////////////////private

void MyGL::drawGame(QList<int*>& cells_em,Field& field,int* ch_em,int phantomx,int phantomy)
{
    phantomPos[0]=phantomx;
    phantomPos[1]=phantomy;
 circ_em=ch_em;
 this->cell_em =&cells_em;
 this->field = &field;
 setFocus();
 update();

}
void MyGL::drawChecker(){
    int  radius=h8>w8?w8/2:h8/2;
    glPushMatrix();
    glTranslatef(radius,radius,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0,0);
    for(int i=0;i<31;i++){
        glVertex2f(radius*sin(i*M_PI/15.0),radius*cos(i*M_PI/15.0));
    }
    glEnd();
    glPopMatrix();
}
void MyGL::drawGod(){
   drawChecker();
   glColor3f(0.9,0.9,0);
   int  radius=h8>w8?w8/2:h8/2;
   glPushMatrix();
   glTranslatef(radius,radius,0);
   radius*=2;
   radius/=4;
   glBegin(GL_TRIANGLE_FAN);
   glVertex2f(0,0);
   for(int i=0;i<31;i++){
       glVertex2f(radius*sin(i*M_PI/15.0),radius*cos(i*M_PI/15.0));
   }
   glEnd();
   glPopMatrix();
}

void MyGL::drawField(){
    int ht,wt;
    glColor3f(0.9,0.8,0.6);
    glBegin(GL_QUADS);
for(int i=0;i<64;i+=2){
       ht=(i/8);
       wt=(i%8+ht%2)*w8;
       ht*=h8;
       glVertex2i(wt,ht);
       glVertex2i(wt,ht+h8);
       glVertex2i(wt+w8,ht+h8);
       glVertex2i(wt+w8,ht);

   }
 glEnd();
}
void MyGL::drawCircleEm(){
    if(!circ_em) return;
     glColor3ub(100,255,100);
 if(circ_em[0]!=-1){
     glPushMatrix();
     glTranslatef(circ_em[0]*w8,circ_em[1]*h8,0);
     int  radius=h8>w8?w8/2:h8/2;
     glTranslatef(radius,radius,0);
     glBegin(GL_TRIANGLE_FAN);
     glVertex2f(0,0);
     for(int i=0;i<31;i++){
         glVertex2f((radius/3)*sin(i*M_PI/15.0),(radius/3)*cos(i*M_PI/15.0));
     }
     glEnd();
     glPopMatrix();
     glPopMatrix();

 }
}


drawSquare(){
}

void MyGL::drawCellsEm()
{if(!cell_em)return;
     glColor3f(0,1,0);
    glBegin(GL_QUADS);
    for(int*a :*cell_em){
    glTranslatef(a[0]*w8,a[1]*h8,0);

       glVertex2i(a[0]*w8,a[1]*h8);
      glVertex2i(a[0]*w8,(a[1]+1)*h8);
      glVertex2i((a[0]+1)*w8,(a[1]+1)*h8);
      glVertex2i((a[0]+1)*w8,a[1]*h8);
   }

    glEnd();
}

void MyGL::drawPhantom()
{
  if(phantomPos[0]==-1)return;
  glColor3f(0.6,0.5,0.4);
  glPushMatrix();
  glTranslatef(phantomPos[0]*w8,phantomPos[1]*h8,0);
  drawChecker();
  glPopMatrix();
}

void MyGL::drawCheckers(){
    if(!field) return;
  for(int i=0;i<4;i++)
      for(int j=0;j<8;j++){
          if(field->cells[i][j]!='-'){
            if(field->cells[i][j]=='b' || field->cells[i][j]=='d')
                glColor3ub(50,50,50);
             else if(field->cells[i][j]=='w'|| field->cells[i][j]=='q')
                 glColor3ub(255,255,255);
            glPushMatrix();
            glTranslatef((i*2+1-j%2)*w8,j*h8,0);
            if(field->cells[i][j]=='b' || field->cells[i][j]=='w')
            drawChecker();
            else
            drawGod();
            glPopMatrix();
          }
      }
}

