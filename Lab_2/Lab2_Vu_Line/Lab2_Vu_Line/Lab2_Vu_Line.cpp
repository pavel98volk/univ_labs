// Lab2_Vu_Line.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL/glut.h>
#include"Siaolin.h"
#include <windows.h>

int x_coord = 0, y_coord = 0;
bool Mstate = false;
using namespace S_Vu;





	void init2D(float r, float g, float b)
	{
		glClearColor(r, g, b, 0.0);
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(0.0, 100.0, 0.0, 100.0);
	}

	void display(void)
	{
		Sleep(10);
		segment(0, 0, x_coord, y_coord,Mstate);
		
	
	}
	
	void mouse(int x, int y) {
			x_coord = x / 15;
			y_coord = (500 - y) / 15;
		
	}

	void m1(int button, int state, int x, int y) {
		if(state == GLUT_UP)
			Mstate = !Mstate;
	}

	//int WinMain(HINSTANCE hInst,HINSTANCE hPrInst,LPCSTR cmdLine,)
	void main(int argc, char *argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(1000, 500);
		glutInitWindowPosition(200, 200);
		glutCreateWindow("points and lines");
		init2D(0.0, 0.0, 0.0);
		glScaled(1.5, 3.0, 1);
		glPointSize(15.0);
		glutPassiveMotionFunc(mouse);
		glutMouseFunc(m1);
		glutDisplayFunc(display);
		glutIdleFunc(display);
		glutMainLoop();
	}


	

