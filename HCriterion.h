#pragma once
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <iomanip>
#include<random>
#include "HFunction.h"
using namespace std;

class Criterion {
	double eps;
	//int STOPindex;//////
public:
	const double get_eps() const;
	Criterion(double epsilon) :eps(epsilon) {
	};
	virtual const bool stop(vector<double>, const  vector<double>&, Function&, int, int = 0) const = 0;
};

class Criterion_grad_norm :public Criterion {
public:
	Criterion_grad_norm(double epsilon = 0.001) :Criterion(epsilon) {};
	virtual const bool stop( vector<double>, const  vector<double>&, Function&, int, int = 0)  const override;
};

class Criterion_num_of_iteration :public Criterion {
	int STOPindex;//вернуть
public:
	Criterion_num_of_iteration(int N = 100000,double epsilon=0.001) :Criterion(epsilon), STOPindex(N) {};
	virtual const bool stop(vector<double> x, const vector<double>& y, Function& f, int num_iteration, int num_iteration_without_change = 0) const override;
};
class Criterion_num_of_nochange_iteration :public Criterion {
	int STOPifno_change;
public:
	Criterion_num_of_nochange_iteration(int N = 1000, double epsilon = 0.001) :Criterion(epsilon),  STOPifno_change(N) {};
	virtual const bool stop( vector<double> x, const vector<double>& y, Function& f, int num_iteration, int num_iteration_without_change = 0) const override;
};

class Criterion_dif_of_f : public Criterion {
public:
	Criterion_dif_of_f(double epsilon = 0.001) :Criterion(epsilon) {};
	virtual const bool stop( vector<double> x, const  vector<double>& y, Function& f, int num_iteration, int num_iteration_without_change = 0) const override;
};

class Criterion_one_dim_norm :public Criterion {
public:
	Criterion_one_dim_norm(double epsilon = 0.001) :Criterion(epsilon) {};
	virtual const bool stop( vector<double> x, const vector<double>& y, Function& f, int num_iteration, int num_iteration_without_change = 0) const override;
};