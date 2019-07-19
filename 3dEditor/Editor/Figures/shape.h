#ifndef SHAPE_H
#define SHAPE_H


#include<QOpenGLFunctions>
#include"vertex.h"
#include"GL/gl.h"

class Shape{
public:
    int ID;
     float rotation[3];
      float translation[3];
      float temp_rotation[3];
      float temp_translation[3];
      float color[3]={200,150,170};
protected:
    int mode;//for example =GL_TRIANGLES;


    float scale[3];
    float temp_scale[3];

    virtual void draw()=0;
public:
    Shape(float x=0,float y=0,float z=0,float x_angle=0,float y_angle=0,float z_angle=0,float x_scale=1,float y_scale=1,float z_scale=1);

   void rotate(float ax,float ay,float az);
   void set_rotation(float ax,float ay,float az);
   void set_temp_rotation(float ax,float ay,float az);
   void translate(float dx,float dy,float dz );
   void set_temp_translation(float x,float y,float z);
   void set_temp_scale(float x,float y,float z);
   void add_scale();
   void set_translation(float x,float y,float z);
   void add_rotations();
   void add_translations();

   void  rotate_from_point(float angle,float ax,float ay,float az,float point_x,float point_y,float point_z){
   }


    void draw_gl();

};
#endif // SHAPE_H
