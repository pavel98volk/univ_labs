#pragma once
#include"parSweep.hpp"
#include<thread>
//this file containes functions for paralel- sweeping method (solves 3-linear equations systems)
template<int par_n, typename T, typename R>
bool par_sweep(T*main, T*sub, T*over, R*res, int n);

//template<typename T, typename R>
//int j_sweep(T*main, T*sub, T*over, R*res, int n_max, int n_min = 1);