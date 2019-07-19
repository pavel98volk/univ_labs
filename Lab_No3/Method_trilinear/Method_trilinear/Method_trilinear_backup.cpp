// Method_trilinear.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<thread>
//substraction for matrix not really needed 
template<typename T>
void sub(T**a, int length, int n1, int n2 ,T multiple = 1) {
	if ((length <= n1) || (length <= n2))return; 
	for (int i = 0;i <= length;i++) {
		a[n1][i] -= a[n2][i] * multiple;
	}
	return;
}

//to change j_sweep and look throuth another cone for div 0 cases
template<typename T>
void swap(T&a,T&b) {
	T c = a;
	a = b;
	b = c;
}

//example of non-paralel method
template<typename T, typename R>
R* just_sweep(T*main, T*sub, T*over, R*res, int n_max) { //n_max ==Number of rows;
	  //is_found used to mark calculated values; () to assign false for each of them;
		bool*is_found = new bool[n_max]();
		T temp;
		for (int i = 1;i < n_max;++i) {
			//what i we have to divide on 0? that means we have " 0 0 over[i-1] " row and r[i] almost found!
			if (main[i - 1] == 0) {
				is_found[i - 1] = true; // r[i-1] found

				if (over[i - 1]) res[i - 1] /= over[i - 1]; //otherwise we don't give a damn what value is better
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
			//else == everything is OK
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

		
		//to delete or not to delete?
		delete[]main;
		delete[]sub;
		delete[]over;
		
		return res;
	}

//ordinary sweep for a part including counting of b and g vectors
   template<typename T,typename R>
R* j_sweep(T*main, T*sub, T*over, R*res, int n_max, int n_min = 1,T*b=nullptr,T*g = nullptr,int bbeg=-1,int gend=-1 ) { //bbeg gend from 0
	{
		T temp;
		if (bbeg >= 0)
		b[bbeg] = sub[n_min - 1];
		for (int i = n_min;i < n_max;++i) {
			temp = sub[i] / main[i - 1];
			main[i] -= temp*over[i - 1];
			res[i] -= temp*res[i - 1];
			if (bbeg >= 0) {
				++bbeg;
				b[bbeg] =- b[bbeg - 1] * temp;
			}
		}
		res[n_max - 1] = res[n_max - 1] / main[n_max - 1];
		if (bbeg >= 0) {
			b[bbeg] /= main[n_max - 1];
			
		}
		if (gend >= 0) {
			g[gend] = over[n_max - 1];
		}
		for (int i = n_max - 2;i >= (n_min - 1);i--) {


			if (bbeg > 0) {  //? was >=
				--bbeg;
				b[bbeg] = (b[bbeg] - over[i] * b[bbeg + 1]) / main[i];
			}
			if (gend >0)// was >=
			{
				--gend; // was bbeg??
				g[gend] = -(g[gend + 1] * over[i])/main[i];
			}
			res[i] = (res[i] - over[i] * res[i + 1]) / main[i];
		}
		//to do or not to do... what?
		

		return res;
	}

}

//paralel sweep;
template<typename T, typename R>
R* par_sweep(T*main, T*sub, T*over, R*res, int n, int par_n) {
	if (n % par_n) return nullptr;
	int n1 = n / par_n;
	T*b = new T[n - n1];
	T*g = new T[n];

	//finding b and g
	for (int i = 0;i < par_n;++i) {
		j_sweep(main, sub, over, res, n1*(i + 1), n1*i + 1, b, g, (i - 1)*(n1), ((i == (par_n - 1)) ? -1 : (n1*(i + 1) - 1)));
	}
	/*
	 now we have :  1 0 0 g0		   R1
					0 1 0 g1		   R2
					0 0 1 g2		   ...
					   b0 1 0 0 g3
					   b1 0 1 0 g4
					   b2 0 0 1 g5
							 b3 1 0 0
							 b4 0 1 0
							 b5 0 0 1


	*/

	/*let's solve
	   1 g0
		 g2 1
		 1 b0 g3
		   b2 g5 1
			  1 b3
				b5 1
		par_n ammount of parts | n1 size of 1 part |
	*/
	{
	T temp1;
	for (int i = 0;i < (par_n - 1);++i) {
		res[n1*(i + 1)] -= res[n1*(i + 1) - 1] / (temp1 = g[n1*(i + 1) - 1]);
		b[n1*i] -= 1 / temp1;

		res[n1*(i + 2) - 1] -= res[n1*(i + 1)] * (temp1 = b[n1*(i + 1) - 1] / b[n1*i]);
		if (i != (par_n - 2))
			g[n1*(i + 2) - 1] -= g[n1*(i + 1)] * temp1;
	}
}

	res[n1*(par_n - 1)] /= b[n1*(par_n - 2)];
	for (int i = par_n-1;i >0;--i) {
		res[n1*i - 1] -= res[n1*i];
		res[n1*i - 1] /= g[n1*i - 1];
		res[n*(i - 1)] = res*[n1*i - 1] * g[n1*(i - 1)];
		if (i != 1);
		res[n*(i - 1)] /= b[n1*(par_n - 2)];
	}
	/*
	now we have	 1 
				   0 1
				   1 0
				       0 1
					   1 0
					       1
	
	SO LET'S SWAP!
	*/
	{
		R temp;
		for (int i = n1;i < n;i += n1) {
		temp = res[i];
		res[i] = res[i - 1];
		res[i - 1] = temp;
		}
	}
	
	// and now we can make it to the end 
	/*here it is our 
	  123456789
	___________|___
	1)1        |   |
	2) 1 g     |   |
	3)  1      |   O
	4)   1     |  /|\
	5)  b 1 g  |   2/par_n of task is made
	6)     1   |  /|
	7)	    1  |
	8)	   b 1 |
	9)	      1|
	
	
	
	*/
	for (int i = 0;i <( par_n);++i) {
		for (int j = 1;j < (n1-1);i++) {
			if (i) {
				res[n1*i + j] -= res[n1*i-1] * b[n1*(i - 1) + j];
			}
			if (i != (par_n - 1)) {
				res[n1*i + j] -= res[n1*(i + 1)] * g[n1*i + j];
			}
		}
	}
	
	return res;
}
int main()
{
	int n;
	std::cin >> n;
	float*main = new float[n];
	float* over = new float[n];
	float* under = new float[n];
	float* res = new float[n];
	std::cin >> main[0] >> over[0] >> res[0];
	for (int i = 1;i < n-1;i++) {
		std::cin >> under[i] >> main[i] >> over[i] >> res[i];
	}
	std::cin >> under[n-1] >> main[n-1] >> res[n-1];
	
	res = just_sweep<float, float>(main, under, over, res, n); // var 1
	//res = j_sweep<float, float>(main, under, over, res, n,n/2);
	
	for (int i = 0;i < n;i++) std::cout << res[i]<< " ";
	system("pause");
    return 0;
}

