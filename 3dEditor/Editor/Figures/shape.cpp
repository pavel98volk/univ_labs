

#include"shape.h"
#include <QDebug>

Shape::Shape(float x,float y,float z,float x_angle,float y_angle,float z_angle,float x_scale,float y_scale,float z_scale){

    translation[0]=x;
    translation[1]=y;
    translation[2]=z;
    rotation[0]=x_angle;
    rotation[0]=y_angle;
    rotation[0]=z_angle;
    scale[0]=x_scale;
    scale[1]=y_scale;
    scale[2]=z_scale;
    temp_rotation[0]=0;
    temp_rotation[1]=0;
    temp_rotation[2]=0;
    temp_translation[0]=0;
    temp_translation[1]=0;
    temp_translation[2]=0;
    temp_scale[0]=0;
    temp_scale[1]=0;
    temp_scale[2]=0;
}

void Shape::rotate(float ax, float ay, float az){// in deg.
    rotation[0]+=ax;
    rotation[1]+=ay;
    rotation[2]+=az;
    rotation[0]-=((int)rotation[0]/360)*360;
    rotation[1]-=((int)rotation[1]/360)*360;
    rotation[2]-=((int)rotation[2]/360)*360;
}

void Shape::set_rotation(float ax, float ay, float az)
{
    rotation[0]=ax;
    rotation[1]=ay;
    rotation[2]=az;
    rotation[0]-=((int)rotation[0]/360)*2*M_PI;
    rotation[1]-=((int)rotation[1]/360)*2*M_PI;
    rotation[2]-=((int)rotation[2]/360)*2*M_PI;
}

void Shape::set_temp_rotation(float ax, float ay, float az)
{
    temp_rotation[0]=ax;
    temp_rotation[1]=ay;
    temp_rotation[2]=az;
    temp_rotation[0]=fmod(temp_rotation[0],360.0);
    temp_rotation[1]=fmod(temp_rotation[1],360.0);
    temp_rotation[2]=fmod(temp_rotation[2],360.0);

}

void Shape::add_rotations()
{
    rotation[0]+=temp_rotation[0];
    rotation[1]+=temp_rotation[1];
    rotation[2]+=temp_rotation[2];
    qDebug()<<"rot "<<temp_rotation[0]<<" "<<temp_rotation[1]<<" "<<temp_rotation[2];
    temp_rotation[0]=0;
    temp_rotation[1]=0;
    temp_rotation[2]=0;
    rotation[0]=fmod(rotation[0],360);
    rotation[1]=fmod(rotation[1],360);
    rotation[2]=fmod(rotation[2],360);

}

void Shape::add_translations()
{
  translation[0]+=temp_translation[0];
  translation[1]+=temp_translation[1];
  translation[2]+=temp_translation[2];
  temp_translation[0]=0;
  temp_translation[1]=0;
  temp_translation[2]=0;
}
void Shape::add_scale()
{
  scale[0]+=temp_scale[0];
  scale[1]+=temp_scale[1];
  scale[2]+=temp_scale[2];
  temp_scale[0]=0;
  temp_scale[1]=0;
  temp_scale[2]=0;
}

void Shape::translate(float dx, float dy, float dz){

    temp_translation[0]+=dx;
    temp_translation[1]+=dy;
    temp_translation[2]+=dz;
}

void Shape::set_temp_translation(float x, float y, float z)
{
   temp_translation[0]=x;
   temp_translation[1]=y;
   temp_translation[2]=z;

}
void Shape::set_temp_scale(float x, float y, float z)
{
   temp_scale[0]=x;
   temp_scale[1]=y;
   temp_scale[2]=z;
}

void Shape::set_translation(float x, float y, float z)
{
    translation[0]=x;
    translation[1]=y;
    translation[2]=z;
 }

void Shape::draw_gl(){
   glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(translation[0],translation[1],translation[2]);
    glTranslatef(temp_translation[0],temp_translation[1],temp_translation[2]);

    glRotatef(temp_rotation[0],1,0,0);
    glRotatef(temp_rotation[1],0,1,0);
    glRotatef(temp_rotation[2],0,0,1);
    glRotatef(rotation[0],1,0,0);
    glRotatef(rotation[1],0,1,0);
    glRotatef(rotation[2],0,0,1);
    glScalef(scale[0]+temp_scale[0],scale[1]+temp_scale[1],scale[2]+temp_scale[2]);
    glColor3ub(color[0],color[1],color[2]);
    draw();
    glPopMatrix();
}
