#ifndef CONE_H
#define CONE_H
#include <GL/gl.h>
#include <math.h>
#define MATH_CONSTANTS;
#include"shape.h"


class Cone:public Shape {
public:
   GLfloat(*circle)[2] = new GLfloat[3][2];
    GLfloat h;
    GLfloat R;
    GLfloat quality;
    GLbyte color[4] = { 12,12,120,10 };

    Cone(GLfloat R,GLfloat h,int quality=10);
    void draw() override;
};
#endif // CONE_H
