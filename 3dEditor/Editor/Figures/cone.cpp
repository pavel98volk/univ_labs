#include "cone.h"


 Cone::Cone(GLfloat R,GLfloat h,int quality){
     ID=1;
     this->h=h;
     this->quality=quality;
     circle=new GLfloat[quality][2];
     float angle=2*M_PI/quality;
     for(int i=0;i<quality;i++){
         circle[i][0]=R*sin((angle*i));
         circle[i][1]=R*cos((angle*i));
     }
 }

 void Cone::draw(){
     float hdt=h/3.0;
     glBegin(GL_TRIANGLE_FAN);
     glNormal3f(0,1,0);
     glVertex3f(0,2*hdt,0);
     for(int i=0;i<(quality);i++){
         glNormal3f(circle[i][0],0,circle[i][1]);
        glVertex3f(circle[i][0],-hdt,circle[i][1]);
     }
     glVertex3f(circle[0][0],-hdt,circle[0][1]);
     glEnd();

     glBegin(GL_TRIANGLE_FAN);
     glNormal3f(0,-1,0);
     glVertex3f(0,-hdt,0);
     for(int i=0;i<(quality);i++){
        glVertex3f(circle[i][0],-hdt,circle[i][1]);
     }
      glVertex3f(circle[0][0],-hdt,circle[0][1]);
     glEnd();
 }
