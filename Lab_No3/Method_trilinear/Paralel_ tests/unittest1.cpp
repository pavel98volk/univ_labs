#include "stdafx.h"
#include "CppUnitTest.h"
#include "Par_3linear.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;



template<typename... T>
void init(float* mas,float el,T...args) {
	mas[0] = el;
	if (!(sizeof...(args)))return;

	init(&(mas[1]), args...);
}
void init(float* mas) {
	return;
}

void Par_sweep_test(float*over, float*main, float*under, float*res,int n) {
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
	bool is_calculated = par_sweep<2>(main, under, over, res, n); // var 1
																  //bool is_calculated = j_sweep<float, float>(main, under, over, res, 3,1);
	if (!is_calculated)return;
	//just_sweep(main, under, over, res, n);

	wchar_t*message = new wchar_t[10];															  //here we can see if resulrt is right
	for (int i = 0;(i < n);i++) {
		float k = 0;
		if (i)k += under_cpy[i] * res[i - 1];
		k += main_cpy[i] * res[i];
		if (i != (n - 1))k += over_cpy[i] * res[i + 1];
		_itow(i, message, 10);
		Assert::IsTrue(fabsf(k - res_cpy[i]) <0.01, message);

	}
	delete[] message;
	delete[] over_cpy;
	delete[] under_cpy;
	delete[] main_cpy;
	delete[] res_cpy;
}
void j_sweep_test(float*over, float*main, float*under, float*res, int n,int start,int end) {
	//making copy to verify result

	float*main_cpy = new float[n];
	float* over_cpy = new float[n];
	float* under_cpy = new float[n];
	float* res_cpy = new float[n];

	for (int i = 0;i < n;i++) {
		main_cpy[i] = main[i];
		under_cpy[i] = under[i];
		res_cpy[i] = res[i];
		over_cpy[i] = over[i];
	}
	bool is_calculated = j_sweep(main, under, over, res, start, end); // var 1
																	  //bool is_calculated = j_sweep<float, float>(main, under, over, res, 3,1);


	if (!is_calculated)return;
	//here we can see if solved part is right

	wchar_t*message = new wchar_t[20], *message1 = new wchar_t[20];
	for (int i = start;(i <= end);i++) {
		float k = 0;
		if (i != start)k += under_cpy[i] * res[i - 1];
		k += main_cpy[i] * res[i];
		if (i != (end))k += over_cpy[i] * res[i + 1];

		wcscat(message, _itow(i, message1, 10));
		Assert::IsTrue(fabsf(k - res_cpy[i]) <0.01, message);

	}
	delete[] message;

	// and here it is checked if other elements left as they were before
	for (int i = 0;(i < start);i++) {
		Assert::IsTrue(over_cpy[i] == over[i], L"over_before_block");
		Assert::IsTrue(main_cpy[i] == main[i], L"main_before_block");
		Assert::IsTrue(under_cpy[i] == under[i], L"sub_before_block");
		Assert::IsTrue(res_cpy[i] == res[i], L"res_before_block");
	}
	for (int i = end + 1;(i < n);i++) {
		Assert::IsTrue(over_cpy[i] == over[i], L"over_after_block");
		Assert::IsTrue(main_cpy[i] == main[i], L"main_after_block");
		Assert::IsTrue(under_cpy[i] == under[i], L"sub_after_block");
		Assert::IsTrue(res_cpy[i] == res[i], L"res_after_block");
	}

	delete[] over_cpy;
	delete[] under_cpy;
	delete[] main_cpy;
	delete[] res_cpy;
}

namespace Paralel_tests
{		
	TEST_CLASS(Paralel_Sweep_Tests)
	{
	public:
		
		TEST_METHOD(par_sweep_test_basic)
		{
			int n = 9;
			float*main = new float[n];
			float* over = new float[n];
			float* under = new float[n];
			float* res = new float[n];

			init(main, 1, 2, 3, 4, 5, 6, 7, 8,9);
			init(over, 5, 4, 8, 3, 6, 4, 6, 0,4);
			init(under, 0, 3, 4, 8, 6, 7, 4, 6,2);
			init(res, 3, 6, 5, 2, 7, 4, 8, 5,12);
			Par_sweep_test(over, main, under, res, n);

			delete[] over;
			delete[] under;
			delete[] main;
		}

		TEST_METHOD(par_sweep_test_zero_matrix)
		{
			int n = 9;
			float*main = new float[n];
			float* over = new float[n];
			float* under = new float[n];
			float* res = new float[n];

			init(over, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			init(main, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			init(under,0, 0, 0, 0, 0, 0, 0, 0, 0);
			init(res,  0, 0, 0, 0, 0, 0, 0, 0, 0);
			Par_sweep_test(over, main, under, res, n);

			delete[] over;
			delete[] under;
			delete[] main;
		}

		TEST_METHOD(par_sweep_test_simle_impossible_matrix)
		{
			int n = 9;
			float*main = new float[n];
			float* over = new float[n];
			float* under = new float[n];
			float* res = new float[n];

			init(main, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			init(over, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			init(under, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			init(res, 0, 0, 0, 0, 0, 0, 0, 1, 0);
			Par_sweep_test(over, main, under, res, n);

			delete[] over;
			delete[] under;
			delete[] main;
		}

		TEST_METHOD(par_sweep_test_advavced_impossible_matrix)
		{
			int n = 9;
			float*main = new float[n];
			float* over = new float[n];
			float* under = new float[n];
			float* res = new float[n];

			
		 init(over, 0, 1, 0, 0, 0, 0, 0, 0, 0);
		 init(main, 0, 1, 1, 0, 0, 0, 0, 0, 0);
	     init(under,0, 0, 1, 0, 0, 0, 0, 0, 0);
		 init(res,  0, 1, 2, 0, 0, 0, 0, 0, 0);
			Par_sweep_test(over, main, under, res, n);

			delete[] over;
			delete[] under;
			delete[] main;
		}

		TEST_METHOD(j_sweep_test_basic)
		{
			int n = 8;
			int start = 2;
			int end = 5;
			//initialising data
			float*main = new float[n];
			float* over = new float[n];
			float* under = new float[n];
			float* res = new float[n];

			init(main, 1, 2, 3, 4, 5, 6, 7, 8);
			init(over, 5, 4, 8, 3, 6, 4, 6, 0);
			init(under, 0, 3, 4, 8, 6, 7, 4, 6);
			init(res, 3, 6, 5, 2, 7, 4, 8, 5);

			j_sweep_test(over, main, under, res, n, start, end);

			delete[] over;
			delete[] under;
			delete[] main;
			delete[] res;
		}

		TEST_METHOD(j_sweep_test_zero_matrix)
		{
			int n = 9;
			int start = 2;
			int end = 6;
			float*main = new float[n];
			float* over = new float[n];
			float* under = new float[n];
			float* res = new float[n];

			init(main, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			init(over, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			init(under, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			init(res, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			j_sweep_test(over, main, under, res, n,start,end);

			delete[] over;
			delete[] under;
			delete[] main;
		}

		TEST_METHOD(j_sweep_test_simle_impossible_matrix)
		{
			int n = 9;
			int start = 3;
			int end = 9;
			float*main = new float[n];
			float* over = new float[n];
			float* under = new float[n];
			float* res = new float[n];

			init(main, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			init(over, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			init(under, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			init(res, 0, 0, 0, 0, 0, 0, 0, 1, 0);
			j_sweep_test(over, main, under, res, n,start,end);

			delete[] over;
			delete[] under;
			delete[] main;
		}

		TEST_METHOD(j_sweep_0_rows_sweeped)
		{
			int n = 8;
			int start = 3;
			int end = 3;
			//initialising data
			float*main = new float[n];
			float* over = new float[n];
			float* under = new float[n];
			float* res = new float[n];

			init(main, 1, 2, 3, 4, 5, 6, 7, 8);
			init(over, 5, 4, 8, 3, 6, 4, 6, 0);
			init(under, 0, 3, 4, 8, 6, 7, 4, 6);
			init(res, 3, 6, 5, 2, 7, 4, 8, 5);

			j_sweep_test(over, main, under, res, n, start, end);

			delete[] over;
			delete[] under;
			delete[] main;
			delete[] res;
		}

		TEST_METHOD(j_sweep_end_before_start)
		{
			int n = 8;
			int start = 4;
			int end = 1;
			//initialising data
			float*main = new float[n];
			float* over = new float[n];
			float* under = new float[n];
			float* res = new float[n];

			init(main, 1, 2, 3, 4, 5, 6, 7, 8);
			init(over, 5, 4, 8, 3, 6, 4, 6, 0);
			init(under, 0, 3, 4, 8, 6, 7, 4, 6);
			init(res, 3, 6, 5, 2, 7, 4, 8, 5);

			j_sweep_test(over, main, under, res, n, start, end);

			delete[] over;
			delete[] under;
			delete[] main;
			delete[] res;
		}

	};

}