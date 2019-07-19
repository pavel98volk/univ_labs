#include "cylinder.h"


 Cylinder::Cylinder(GLfloat R,GLfloat h,int quality){
     ID=2;
     this->h=h;
     this->R=R;
     this->quality=quality;
     circle=new GLfloat[quality][2];
     float angle=2*M_PI/quality;
     for(int i=0;i<quality;i++){
         circle[i][0]=R*sin((angle*i));
         circle[i][1]=R*cos((angle*i));
     }
 }

 void Cylinder::draw(){
     float hdt=h/2.0;
     glBegin(GL_TRIANGLE_FAN);
     glNormal3f(0,1,0);

     glVertex3f(0,hdt,0);
     for(int i=0;i<(quality);i++){
        glVertex3f(circle[i][0],hdt,circle[i][1]);
     }
     glVertex3f(circle[0][0],hdt,circle[0][1]);
     glEnd();

     glBegin(GL_TRIANGLE_FAN);
     glNormal3f(0,-1,0);
     glVertex3f(0,-hdt,0);
     for(int i=0;i<(quality);i++){

        glVertex3f(circle[i][0],-hdt,circle[i][1]);
     }
      glVertex3f(circle[0][0],-hdt,circle[0][1]);
     glEnd();
     glBegin(GL_TRIANGLE_STRIP);

     for(int i=0;i<(quality);i++){
         glNormal3f(circle[i][0]/R,0,circle[i][1]/R);
        glVertex3f(circle[i][0],-hdt,circle[i][1]);
         glVertex3f(circle[i][0],hdt,circle[i][1]);
     }
      glVertex3f(circle[0][0],-hdt,circle[0][1]);
      glVertex3f(circle[0][0],+hdt,circle[0][1]);
     glEnd();

 }
