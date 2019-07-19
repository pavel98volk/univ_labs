// Method_trilinear.cpp : Defines the entry point for the console application.
//

//--------------------------------------IT IS EASIER TO USE SOME KIND OF MATRIX ,BUT THIS SOLUTION MIGHT BE FASTER -----------------------
#include "stdafx.h"
#include<iostream>
#include"Par_3linear.h"
//substraction for matrix not really needed 



//example of non-paralel method
template<typename T, typename R>
bool just_sweep(T*main, T*sub, T*over, R*res, int n_max) { //n_max ==Number of rows;
	  //is_found used to mark calculated values; () to assign false for each of them;
		bool*is_found = new bool[n_max]();
		for (int i = 1;i < n_max;++i) {
			//what if we have to divide on 0? that means we have " 0 0 over[i-1] " row and r[i] almost found!
			if (!main[i - 1] && over[i - 1]) {
				is_found[i - 1] = true; // r[i] found;why not isfound[i] explained at the end where we use swap()

				 res[i - 1] /= over[i - 1];
				res[i] -= res[i - 1] * main[i];    //getting rid of this variable from next row


				if ((i + 1) < n_max) {
					res[i + 1] -= res[i - 1] * sub[i + 1];//the same for next next row
					sub[i + 1] = 0; // cause value under the new main[i] is 0;(to row striking out)
				}
				// now we gonna emulate striking out row[i-1] and column[i-1];
				main[i] = sub[i];
				sub[i] = 0;
				
				//now we can pass to the next iteration with a clear heart
			}
			else if (!main[i - 1]) {
				if (res[i - 1])return false;
				else {
					//_____________HOW???????????????????RECURSIVE?
					return false;
				}
			}
			//else == MOSTLY everything is OK
			else {
				 over[i-1]/= main[i - 1];
				 res[i - 1] /= main[i - 1];
				 main[i] -=sub[i]*over[i - 1];
				 res[i] -= sub[i]*res[i - 1];
			}
		}
		if (main[n_max-1] !=0) res[n_max - 1] /= main[n_max - 1]; // our algorhytm left last row without dividing it on main[last] to get 1 at the bottom corner so here we do it;
		/*
		Here we have	1 x0 0 0 0... |rol
		                0 1 x1 0 0 ...|r1
						....
						.....
						0 0  0 0 ..0 1|r(n-1)
			Don't forget about found variables! The real look of this matrix can be far less pleasent
			but we have bool array to handle this problemm
		*/
		//here we gow from the bottom to the top

			for (int i = n_max - 2;i >= 0;i--) {
				int next = i + 1;
				while (is_found[i])--i;
				
				if(i>=0)res[i]-= over[i] * res[next];
			}

			//back when we handled div 0 , we found r[i] and left it at r[i-1] place;so we had either to swap everything then or swap results only now
			for (int i = n_max-1;i >-1;--i) {
				if (is_found[i]) swap(res[i], res[i + 1]);
			}

		delete[]is_found;
		
		
		return true;
	}



int main()
{
	std::cout << "Enter order of matrix: ";
	int n;
	std::cin >> n;
	float*main = new float[n];
	float* over = new float[n];
	float* under = new float[n];
	float* res = new float[n];

	std::cout << "Now enter 3-diagonal  matrix ,each row contains 4 elements: lower diagonal, main diagonal, upper diagonal and result value\n";
		std::cout << "first row has no lower diagonal el:\n";
		
	std::cin >> main[0] >> over[0] >> res[0];
	for (int i = 1;i < n-1;i++) {
		std::cin >> under[i] >> main[i] >> over[i] >> res[i];
	}
	std::cin >> under[n-1] >> main[n-1] >> res[n-1];
	
	float*main_cpy = new float[n];
	float* over_cpy = new float[n];
	float* under_cpy = new float[n];
	float* res_cpy = new float[n];
	//making copy to verify result
	for (int i = 0;i < n;i++) {
		main_cpy[i] = main[i];
		under_cpy[i] = under[i];
		res_cpy[i] = res[i];
		over_cpy[i] = over[i];
	}

	under[0] = over[n - 1] = 0;
	bool is_calculated= par_sweep<2>(main, under, over, res, n); 
	

	if (is_calculated) {
		for (int i = 0;i < n;i++) 
			std::cout << res[i] << " ";
		std::cout << '\n';
	}
	else {
		std::cout << "failed";
	}
	system("pause");
    return 0;
}

