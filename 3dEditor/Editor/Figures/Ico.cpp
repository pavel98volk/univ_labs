
#include "Ico.h"


Ico::~Ico(){


}

Ico::Ico(GLfloat R):Shape() {
    ID=0;

    float GOLDEN = (1.0 + sqrt(5.0)) / 2.0;
    this->R =R;
    R/=sqrt(1 + GOLDEN*GOLDEN);
	float** vertices = new float*[12];
	for (int i = 0;i < 12;i++) vertices[i] = new float[3];
	for (int i = 0;i < 3;i++)
		for (int j = 0;j < 4;j++) {
			vertices[i * 4 + j][i] = (j % 2) ? R : -R;
            vertices[i * 4 + j][(i + 1) % 3] = (j < 2) ?(GOLDEN*R): (-GOLDEN*R);
			vertices[i * 4 + j][(i + 2) % 3] = 0;
		}

	// 5 faces around point 0
	Faces.push_back(initFace(vertices[1], vertices[5], vertices[0]));
	Faces.push_back(initFace(vertices[5], vertices[11], vertices[0]));
	Faces.push_back(initFace(vertices[11], vertices[10], vertices[0]));
	Faces.push_back(initFace(vertices[10], vertices[7], vertices[0]));
	Faces.push_back(initFace(vertices[7], vertices[1], vertices[0]));

	// 5 adjacent faces
	Faces.push_back(initFace(vertices[1], vertices[5], vertices[9]));
	Faces.push_back(initFace(vertices[5], vertices[11], vertices[4]));
	Faces.push_back(initFace(vertices[11], vertices[10], vertices[2]));
	Faces.push_back(initFace(vertices[10], vertices[7], vertices[6]));
	Faces.push_back(initFace(vertices[7], vertices[1], vertices[8]));
	// 5 faces around point 3
	Faces.push_back(initFace(vertices[3], vertices[9], vertices[4]));
	Faces.push_back(initFace(vertices[3], vertices[4], vertices[2]));
	Faces.push_back(initFace(vertices[3], vertices[2], vertices[6]));
	Faces.push_back(initFace(vertices[3], vertices[6], vertices[8]));
	Faces.push_back(initFace(vertices[3], vertices[8], vertices[9]));
	// 5 adjacent faces
	Faces.push_back(initFace(vertices[4], vertices[9], vertices[5]));
	Faces.push_back(initFace(vertices[2], vertices[4], vertices[11]));
	Faces.push_back(initFace(vertices[6], vertices[2], vertices[10]));
	Faces.push_back(initFace(vertices[8], vertices[6], vertices[7]));
	Faces.push_back(initFace(vertices[9], vertices[8], vertices[1]));

    refine();
    refine();
}
GLfloat** Ico::initFace(float*a, float*b, float*c) {

	GLfloat** res = new GLfloat*[3];
	res[0] = a;
	res[1] = b;
	res[2] = c;
	return res;
}


GLfloat* Ico::middle(GLfloat*a, GLfloat*b) {
	GLfloat* c = new float[3];
    c[0] = (a[0] + b[0]) / (2);
    c[1] = (a[1] + b[1]) / (2);
    c[2] = (a[2] + b[2]) / (2);
	float c_norm = sqrt((c[0] * c[0] + c[1] * c[1] + c[2] * c[2]));
	c[0] *= R / c_norm;
	c[1] *= R / c_norm;
	c[2] *= R / c_norm;

	return c;


}

void Ico::refine() {
	GLfloat temp;
	std::list < GLfloat**>*  Faces_next = new std::list < GLfloat**>;
	GLfloat* am, *bm, *cm;
    for(GLfloat** a: Faces) {
		GLfloat* am = middle(a[0], a[1]);
		GLfloat* bm = middle(a[1], a[2]);
		GLfloat* cm = middle(a[2], a[0]);

		(*Faces_next).push_back(initFace(a[0], am, cm));

		(*Faces_next).push_back(initFace(a[1], am, bm));
		(*Faces_next).push_back(initFace(a[2], bm, cm));
        (*Faces_next).push_back(initFace(am, bm, cm));

	}
    Faces.clear();
	Faces = *Faces_next;
}

void Ico::draw() {
	glBegin(GL_TRIANGLES);
	//glMaterialfv();
    for(GLfloat** a: Faces) {
        x[0] = (a[0][0] + a[1][0] + a[2][0])/(3*R);
        x[1] = (a[0][1] + a[1][1] + a[2][1])/(3*R);

        x[2] = (a[0][2] + a[1][2] + a[2][2])/(3*R);


         glNormal3fv(x);
        //glNormal3f(a[0][0]/R,a[0][1]/R,a[0][2]/R);
		glVertex3fv(a[0]);


        //glNormal3f(a[1][0]/R,a[1][1]/R,a[1][2]/R);
		glVertex3fv(a[1]);


        //glNormal3f(a[2][0]/R,a[2][1]/R,a[2][2]/R);
		glVertex3fv(a[2]);

	}
	glEnd();
}
