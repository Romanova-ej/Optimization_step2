#pragma once
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <iomanip>
#include "HArea.h"
#include <memory>
#include<random>
#include "Hother.h"
using namespace std;
/**
\file
\brief Header file describing the class Function and its heirs
*/

/**
\brief Abstract base class for a multidimensional functions and information about it
*/
class Function {
protected:
	int dim;
	const double DELTA = 0.000000001;
	Area D;
public:
	Function(const Area& d);
	Function();
	void setDim(const int);
	int const getDim() const;
	const Area& getArea() const;
	virtual const  double f(const vector<double>&) const = 0;
	~Function();
	virtual const char* getFunctionName() const = 0;

	/**
	\brief It calculates numerically the gradient at the point x of a function, or exactly if the gradient is explicitly defined in the derived class
	\param[in] x vector
	\return gradf(x)
	*/

	virtual  vector<double> getGradient(const vector<double>& x) const;

	/**
	\brief It calculates the numerically derivative of the objective function at the point x in a given direction
	\param[in] x vector-point
	\param[in] p directing vector
	*/
	double getDirectionalDerivative(const vector<double>& x, 
		const vector<double>&p) const;
	const double  operator()(const vector<double>& x);
	/**
	\brief It computes the norm of the vector x
	*/
	friend double norm(const vector<double>& x);
	/**
	\brief It computes the scalar product between the vectors a and b
	*/
	friend double scalar_prod(const vector<double>& a, 
		const vector<double>& b);
	friend const vector<double> operator*(const double a, 
		const vector<double> &B);
	friend vector<double> operator+(const vector<double>& a,
		const vector<double> &b);
};
/**
\brief Function of two variables
*/
class Fun1 :public Function {
public:
	Fun1();
	Fun1(const Area& d);
	virtual const char* getFunctionName() const override;
	virtual const  double f(const vector<double>& x)const override;
};

/**
\brief Quadratic Function of four variables
*/
class Fun2 :public Function {
public:
	Fun2();
	Fun2(const Area& d);
	virtual const double f(const vector<double>&) const override;
	virtual vector<double> getGradient(const vector<double>&);
	virtual const char* getFunctionName() const override;
};

/**
\brief Quadratic Function of two variables
*/
class Fun3 :public Function {
public:
	Fun3();
	Fun3(const Area& d);
	virtual const double f(const vector<double>&)const override;
	virtual const char* getFunctionName() const override;
};

/**
\brief  Function of two variables
*/
class Fun4 :public Function {//x=(1,1),  f=0;
public:
	Fun4();
	Fun4(const Area& d);
	virtual const char* getFunctionName() const override;
	virtual const double f(const vector<double>& x)const override;
};

/**
\brief  Function of four variables
*/
class Fun5 :public Function {//x=(0,0,0,0), f=0
public:
	Fun5();
	Fun5(const Area& d);
	virtual const char* getFunctionName() const override;
	virtual const double f(const vector<double>& x)const override;
};

