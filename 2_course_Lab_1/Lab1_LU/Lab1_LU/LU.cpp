#include"stdafx.h"

#include"LU-decomposition.h"
//#include "InputOutput.h"

 float** LU::makeLU(float**a, int n) {

	float**  res_M = new float*[n];
	for (int i = 0;i < n;i++)
		res_M[i] = new float[n];

	for (int i = 0;i < n;i++) res_M[0][i] = a[0][i];
	float temp;
	for (int i = 0;i < (n - 1); ) {
		for (int j = i + 1;j < n;j++) {
			temp = a[j][i];
			for (int k = 0;k < i;k++) temp -= res_M[j][k] * res_M[k][i];

			if (res_M[i][i])temp /= res_M[i][i]; else temp = 0;  // 
			res_M[j][i] = temp;
		}
		i++;  //incrementation in cycle;
		for (int j = i;j < n;j++) {
			temp = a[i][j];
			for (int k = 0;k < i;k++) temp -= res_M[i][k] * res_M[k][j];
			res_M[i][j] = temp;
		}
	}
	return res_M;
}




float* LU::find_X(float** a, float* b, int n) {
	float**UL = LU::makeLU(a, n);
	//showMatrix(UL, n);
	float*res = new float[n]; //now used to contain y(intermideate vector);

	for (int i = 0;i < n;i++) {
		res[i] = b[i];
		for (int j = 0;j < i;j++)
			res[i] -= res[j] * UL[i][j];

	}

	//and now making res to final result
	for (int i = (n - 1);i >= 0;i--) {
		for (int j = (n - 1);j > i;j--)
			res[i] -= res[j] * UL[i][j];
		if (UL[i][i])res[i] /= UL[i][i]; else res[i] = 0; //
	}

	for (int i = 0;i < n;i++)delete[] UL[i];
	delete[] UL;

	return res;
}