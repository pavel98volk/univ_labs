#pragma once
#include <GL/gl.h>
#include<list>
#include<math.h>

class Ico {
public:
	GLfloat R; //radius
	std::list < GLfloat**> Faces;
	GLbyte color[4] = { 12,12,120,10 };

	Ico(GLfloat R);
	GLfloat** initFace(float*a, float*b, float*c);
	GLfloat* middle(GLfloat*a, GLfloat*b);
	void refine();

	float*x = new float[3];
	void draw();
};
