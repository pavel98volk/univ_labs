#include"Siaolin.h"
#include<GL/glut.h>
#include "windows.h"

namespace S_Vu{
	

	void segment(int x1, int y1, int x2, int y2,bool Vu_enabled) {
	

		// first some math;
		if (x2 < x1) {
			int x3 = x2;
			x2 = x1;
			x1 = x3;
			x3 = y1;
			y1 = y2;
			y2 = x3;
		}




		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POINTS);


		if (Vu_enabled) {
			float dy = (x2 - x1) / static_cast<float>(y2 - y1);
			for (int i = x1; i <= x2; i++) {
				glVertex2i(i, (int)((y1 += dy)));
			}
			glEnd();
			glFlush();
			return;
		}




		if (y1 == y2) {
			for (int i = x1; i <= x2; i++)
				glVertex2i(i, y1);
		}
		else if (x1 == x2) {
			for (int i = y1; i <= y2; i++)
				glVertex2i(x1, i);
		}
		else {
			float dy = (x2 - x1) / static_cast<float>(y2 - y1);
			if (((x2 - x1)> abs(y2 - y1))) {
				float dy = (y2 - y1) / static_cast<float>(x2 - x1);
				float curry = y1, temp;
				for (int i = x1; i <= x2; i++)
				{
					temp = curry - (int)curry;
					glColor3f(temp, temp, temp);
					glVertex2i(i, (int)curry + 1);
					temp = 1 - temp;
					glColor3f(temp, temp, temp);
					glVertex2i(i, (int)curry);
					curry += dy;
				}
			}
			else {
				if (y2 < y1) {
					int x3 = x2;
					x2 = x1;
					x1 = x3;
					x3 = y1;
					y1 = y2;
					y2 = x3;
				}
				float dx = (x2 - x1) / static_cast<float>(y2 - y1);
				float currx = x1, temp;
				for (int i = y1; i <= y2; i++)
				{
					temp = currx - (int)currx;
					glColor3f(temp, temp, temp);
					glVertex2i((int)currx + 1, i);
					temp = 1 - temp;
					glColor3f(temp, temp, temp);
					glVertex2i((int)currx, i);
					currx += dx;
				}

			}
		}
		glEnd();
		glFlush();
	}
}



