#include "stdafx.h"
#include "CppUnitTest.h"
#include "LU-decomposition.h"
#include "LU.cpp"
#include "inputOutput.h"
#include <fstream>
#include<iostream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;
template<typename... T>
void init(float* mas, float el, T...args) {
	mas[0] = el;
	if (!(sizeof...(args)))return;

	init(&(mas[1]), args...);
}
void init(float* mas) {
	return;
}

float find_matr_el(int y, int x, float**UL) {
	int min_x_y = x > y ? y : x;
	float res = 0;
	for (int i = 0;i <= min_x_y; i++)
		res += LU::L_el(y, i,UL)*LU::U_el(i, x,UL);
	return res;
}
namespace LU_tests
{		
	TEST_CLASS(LU_Test)
	{
	public:
		
		TEST_METHOD(Make_UL_UxL_equals_original)
		{
			
			int n = 5;
			float**matr = new float*[n];
			for (int i = 0;i < n;i++)matr[i] = new float[n];

			init(matr[0], 1, 2, 3, 4, 5);
			init(matr[1], 5, 4, 8, 3, 6);
			init(matr[2], 0, 3, 4, 8, 6);
			init(matr[3], 3, 6, 5, 2, 7);
			init(matr[4], 6, 7, 8, 9, 11);
			
			
			
			showMatrix(matr, n);
			float ** res = LU::makeLU(matr, n);
			for (int i = 0;i < n;i++)
				for (int j = 0;j < n;j++) {
						Assert::IsTrue((matr[i][j] - find_matr_el(i, j, res)) < 0.01);
				}
			for (int i = 0;i < n;i++) delete[]matr[i];
			delete[]matr;
		}

	};
}