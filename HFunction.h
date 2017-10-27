#pragma once
#include "stdafx.h"
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <iomanip>
#include<random>
using namespace std;

class Function {
	int dim;
	const double delta = 0.000000001;//по сути эта точность относится только к функциям
public:
	void set_dim(const int);
	int const get_dim() const;
	virtual const  double f(const vector<double>&) = 0;
	~Function();
	virtual const char* get_function_name() const = 0;
	virtual  vector<double> grad(const vector<double>& );
	double directional_derivative(const vector<double>& x, const vector<double>& );
	double  operator()(const vector<double>& x);
	friend double norm(const vector<double>& x);
	friend double scalar_prod(const vector<double>& a, const vector<double>& b);
	friend const vector<double> operator*(const double a, const vector<double> &B);
	friend vector<double> operator+(const vector<double>& a, const vector<double> &b);
};
class fun1 :public Function {
public:
	fun1();
	virtual const char* get_function_name() const override;
	virtual const  double f(const vector<double>& x) override;
};

class fun2 :public Function {
public:
	fun2();
	virtual const double f(const vector<double>&) override;
	virtual vector<double> grad(const vector<double>&);
	virtual const char* get_function_name() const override;
};
class fun3 :public Function {
public:
	fun3();
	virtual const double f(const vector<double>&) override;
	virtual const char* get_function_name() const override;
};
class fun4 :public Function {// решения: x=(1,1),  f=0;
public:
	fun4();
	virtual const char* get_function_name() const override;
	virtual const double f(const vector<double>& x) override;
};

class fun5 :public Function {// решения: (0,0,0,0)  0
public:
	fun5();
	virtual const char* get_function_name() const override;
	virtual const double f(const vector<double>& x) override;
};

