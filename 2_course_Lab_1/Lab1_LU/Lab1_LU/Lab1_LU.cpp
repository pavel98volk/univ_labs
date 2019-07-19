// Lab1_LU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LU-decomposition.h"
#include "InputOutput.h"
#include<iostream>



int main()
{   // input should look like :   1 2 3  29
	//							  4 5 6  438
	//							  7 8 9  489
	//		but first you need to enter n - the order of the matrix				
	float**a = nullptr, *b = nullptr;
	int n;
	std::cout <<"enter order of matrix: ";
	std::cin >> n;
	std::cout << "Now enter matrix:\n";
	input(n,a, b);
	float* res = LU::find_X(a, b, n);

	for (int i = 0;i < n;i++) std::cout << res[i] << " ";
	system("pause");
	delete[] res;
	for (int i = 0;i < n;i++)  delete[]a[i];
	delete[] a;

    return 0;
}

