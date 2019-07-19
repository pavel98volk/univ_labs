#pragma once
#include<iostream>

// using LU - decomposition method to solve matrix n*(n+1);
#define private public // for tests;

class LU {
private:
	//L and U are stored in the same sqare matrix (L matrix has 1 valued diagonal el  so it is'nt stored);
	static float** makeLU(float**, int);
	//to access value of particular U or L el you can use U_el and L_el;
	//only for debug;When using first validate x y; 
	static float U_el(int y, int x, float**LU) {
		if (x < y)return 0;
		else return LU[y][x];
	}
	static float L_el(int y, int x, float**LU) {
		if (x > y) return 0;
		else if (x == y) return 1;
		else return LU[y][x];
	}



public:
	static float* find_X(float** a, float* b, int n);


	
};
 


