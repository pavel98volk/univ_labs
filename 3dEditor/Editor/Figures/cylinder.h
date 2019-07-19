#ifndef CYLINDER_H
#define CYLINDER_H


#include <GL/gl.h>
#include <math.h>
#include"shape.h"
#define MATH_CONSTANTS;

class Cylinder:public Shape{
public:
    GLfloat(*circle)[2] = new GLfloat[3][2];
    GLfloat h;
    GLfloat R;
    GLfloat quality;
Cylinder(GLfloat R,GLfloat h,int quality=10);
 protected:

    void draw();
};


#endif // CYLINDER_H
