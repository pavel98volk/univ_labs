#pragma once
#include "stdafx.h"

#include"Par_3linear.h"

//to change j_sweep and look throuth another cone for div 0 cases
template<typename T>
void swap(T&a, T&b) {
	T c = a;
	a = b;
	b = c;
}

namespace {
	//here we're using sub to contain b and over to contain g
	//is_found[k] used to a) for k<i to exclude row | b)for k>=i to say that sub[k] contains b[k] and original sub[k] == 0;
	template<typename T, typename R>
	int j_sweep(T*main, T*sub, T*over, R*res, int n_min, int n_max) { //sub[0] = over[N-1] = 0 !!!
		if (n_min >= n_max)return false;
		bool*is_found = new bool[(n_max+1)]();
		for (int i = (n_min+1);i <=n_max;++i) {

			if ((!main[i - 1]) && over[i - 1]) {
				is_found[i - 1] = true;


				res[i - 1] /= over[i - 1];
				sub[i - 1] /= over[i - 1];

				over[i - 1] = 0;//(g[i-1] = 0) that is used cause we have no need to use this row in 2nd part when we exclude upper row;


				res[i] -= res[i - 1] * main[i];

				main[i] = is_found[i] ? 0 : sub[i];   // case  sub[i] contains b[i] so sub[i] ==0;
				if (!is_found[i])sub[i] = 0;
				sub[i] -= sub[i - 1] * main[i];
				if ((i + 1) < (n_max+1)) {
					res[i + 1] -= res[i - 1] * sub[i + 1];
					sub[i + 1] *= -sub[i - 1];   //sub[i+1] was never changed before// here we must act carefully; in just_sweep() we used to analyse sub[i-1] value after this point,so here we shoud prevent that
					is_found[i + 1] = true;// that can help us to find out that sub is actually 0;
				}

			}
			else if (!main[i - 1]) {
				//////////////////////////////////////////////////////////////////////TO    DO////////////////////////////////////
				return false;
				/*if (sub[i - 1]) {
				res[i - 1] /= sub[i - 1];
				sub[i - 1] = 1;
				}
				for (int j = (n_min+1);j < (i - 1);i++) {
				res[j] -= sub[j] * res[i - 1];
				sub[j] = 0;
				}

				int k = j_sweep(main, sub, over, res, (n_max+1), i + 1);
				if (!k) {
				main[i - 1] = 1;
				for (int j = i;j < (n_max+1);i++) {
				res[j] -= sub[j] * res[i - 1];
				sub[j] *= sub[i - 1];
				}

				}
				for (int j = (n_min+1);j < (i - 1);i++) {
				res[j] -= sub[j] * res[i - 1];
				sub[j] == 0;
				}*/
			}


			//else == everything is OK
			else {
				over[i - 1] /= main[i - 1];
				res[i - 1] /= main[i - 1];
				sub[i - 1] /= main[i - 1]; //our b
				if (!is_found[i]) {
					main[i] -= sub[i] * over[i - 1];
					res[i] -= sub[i] * res[i - 1];
					sub[i] *= -sub[i - 1];  // now we have the next b in sub[i];
				} //otherwise sub[i] == 0 and we should do nothing
			}
			is_found[i] = false;
		}

		if (main[n_max] != 0) {
			res[n_max] /= main[n_max];
			sub[n_max] /= main[n_max];
			over[n_max] /= main[n_max];
		}


		for (int i = n_max-1;i >=n_min;i--) {
			int next = i + 1;
			while (is_found[i])--i;

			if (i >= 0) {
				res[i] -= over[i] * res[next];
				sub[i] -= over[i] * sub[next];
				over[i] *= -over[next];
			}
		}

		//back when we handled div 0 , we found r[i] and left it at r[i-1] place;so we had either to swap everything then or swap results only now
		for (int i = n_max;i >= ((n_min+1) - 1);--i) {
			if (is_found[i]) {
				swap(res[i], res[i + 1]);
				swap(sub[i], sub[i + 1]);
				swap(over[i], over[i + 1]);

			}
		}

		return true;
	}
}

//paralel sweep;


template<int par_n, typename T, typename R>
bool par_sweep(T*main, T*sub, T*over, R*res, int n) { // result is in res
	if (n < 1) return false;
	if (n < par_n)return false;
	if (n < (2 * par_n)) return false; // can be fixed ; but  n must be >= 2*par_n otherwise sweeping part in second part of this function should be modified 

	sub[0] = over[n - 1] = 0; //to be sure it is;

	int n1 = n / par_n;  // n1 - capacity of each thread


	std::thread t[par_n - 1];//finding b and g
	for (int i = 0;i < (par_n - 1);++i) {
		t[i] = std::thread(j_sweep<T, R>, main, sub, over, res, n1*i, (n1*(i + 1)-1));
	}
	j_sweep<T, R>(main, sub, over, res, n1*(par_n - 1), n-1);

	for (int i = 0;i < (par_n - 1);++i) {
		t[i].join();  // should get values to pass exeptions
	}


	//for (int i = 0;i < n;i++) std::cout << sub[i] << " " << res[i] << " " << over[i] << '\n';std::cout << '\n';
	if (!Last_1st_el_sweep(main, sub, over, res, n, par_n)) return false;

	

	// and now we can make it to the end 
	/*here it is our
	  123456789
	___________|___
	1)1        |   |
	2) 1 g     |   |
	3)  1      |   O
	4)   1     |  /|\
	5)  b 1 g  |   |   
	6)     1   |  /|
	7)	    1  |  
	8)	   b 1 |
	9)	      1|



	*/
	for (int i = 0;i <(par_n - 1);++i) {
		for (int j = 1;j < (n1 - 1);j++) {
			if (i) {
				res[n1*i + j] -= res[n1*i - 1] * sub[n1*i + j];
			}
			res[n1*i + j] -= res[n1*(i + 1)] * over[n1*i + j];
		}
	}
	for (int j = n1*(par_n - 1) + 1;j < (n - 1);j++) { // ag
		res[j] -= res[n1*(par_n - 1) - 1] * sub[j];
	}
	return true;
}

//sweeps first and last rows/columns in each section
template< typename T, typename R>
bool Last_1st_el_sweep(T*main, T*sub, T*over, R*res, int n, int par_n) {
	int n1 = n / par_n;
	/*
	now we have : 
	1 0 0 g0		   R1
	0 1 0 g1		   R2
	0 0 1 g2		   ...
	   b0 1 0 0 g3
	   b1 0 1 0 g4
	   b2 0 0 1 g5
	         b3 1 0 0
	         b4 0 1 0
	         b5 0 0 1


	*/

	/*let's solve EXAMPLE:
	1 g0
	  g2 1
	  1 b3 g3
	    b5 g5 1
	        1 b6
	          b8 1
	par_n ammount of parts | n1 size of 1 part |
	sub contain b over - g ;
	*/
	{
		T temp1; 
		//here we sweeping matrix that's showed above ,
		for (int i = 1;i < par_n;i++) {
		// example substracting 2 row  from 3 ; (g2 1) and (1 b3 g3)
		if (!over[n1*i - 1])
				return false;    // must be partly solved in the future------------------------------------------------------------------------------------------


			res[n1*i] -= res[n1*i - 1] / over[n1*i - 1];
			sub[n1*i] -= 1 / over[n1*i - 1];

			// example substracting 3 row  from 4 ; (0 b3 g3) and (b5 g5 1)
			if (!sub[n1*i])
				return false; // can be partly solved---------------------------------------------------------------------------------------------------------------

			int No_next = (i == (par_n - 1)) ? (n - 1) : (n1*(i + 1) - 1);

			temp1 = sub[No_next] / sub[n1*i];
			res[No_next] -= res[n1*i] * temp1;//last section has has x != n1 el that's why you see -?-:- operator;
			if (i != (par_n - 1))
				over[No_next] -= over[n1*(i)] * temp1;
		}
	}

	//second part:getting rid of upper diagonal
	for (int i = par_n - 1;i > 0;--i) {
		res[n1*i] /= sub[n1*i]; // example: normalising row 5


		res[n1*i - 1] -= res[n1*i];
		//over[n1*i - 1] -= 1 / sub[n1];
		res[n1*i - 1] /= over[n1*i - 1];//normalising row 4 
		res[n*(i - 1)] -= res[n1*i - 1] * over[n1*(i - 1)];

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
	for (int i = n1;i < (par_n*n1 - 1);i += n1) {
		swap(res[i], res[i - 1]);
	}

	return true;
}
