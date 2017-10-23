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
	void set_dim(int);
	int const get_dim() const;
	virtual double f(vector<double>) = 0;
	~Function();
	virtual const char* get_function_name() const = 0;
	virtual vector<double> grad(const vector<double>& );
	double directional_derivative(vector<double> x, vector<double> );
	friend double norm(vector<double>& x);
	friend double scalar_prod(vector<double> a, vector<double> b);
	friend const vector<double> operator*(const double a, const vector<double> &B);
	friend vector<double> operator+(const vector<double>& a, const vector<double> &b);
};
class fun1 :public Function {
public:
	fun1();
	virtual const char* get_function_name() const override;
	virtual double f(vector<double> x) override;
};

class fun2 :public Function {
public:
	fun2();
	virtual double f(vector<double>) override;
	virtual vector<double> grad(const vector<double>&);
	virtual const char* get_function_name() const override;
};