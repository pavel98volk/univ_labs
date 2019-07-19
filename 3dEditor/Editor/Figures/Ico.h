#pragma once
#include <GL/gl.h>
#include<list>
#include<math.h>
#include"shape.h"
class Ico:public Shape {
public:
	GLfloat R; //radius
	std::list < GLfloat**> Faces;
	GLbyte color[4] = { 12,12,120,10 };

    GLfloat** initFace(float*a, float*b, float*c);
    GLfloat* middle(GLfloat*a, GLfloat*b);
    void refine();
	Ico(GLfloat R);
    ~Ico();
	float*x = new float[3];
 protected:
	void draw();
};
