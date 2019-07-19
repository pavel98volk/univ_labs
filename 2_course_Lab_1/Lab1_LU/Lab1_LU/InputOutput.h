#pragma once
#include <iostream>


void showMatrix(float** matr, int n) {
	for (int j = 0;j < n;j++) {
		for (int i = 0;i < n;i++) std::cout << matr[j][i] << ' ';
		std::cout << '\n';
	}
}
void input(int n, float**(&matr), float*(&vec)) { // matr matrix n*n | vec  vector of values (last column))
	vec = new float[n];
	 matr = new float*[n];

	for (int i = 0;i < n;i++) {
	 matr[i] = new float[n];
	 for (int j = 0;j < n;j++) std::cin >> matr[i][j];
	 std::cin >> vec[i];
	}
	return;
}