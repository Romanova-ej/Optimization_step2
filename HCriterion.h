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
/**
\file
\brief Header file describing the class Criterion and its heirs
*/

/**
\brief Abstract base class for various criteria for stopping iterative methods
Class objects are determined by the accuracy of eps
*/
class Criterion {
	double eps;
	int stopIndex;
public:
	const double getEps() const;
	const bool stopIfMoreIteration(int nIteration) const;
	Criterion(double epsilon, int stopId) :eps(epsilon), stopIndex(stopId) {
	};
	virtual const bool stop(vector<double>, const  vector<double>&, Function&,
		int, int = 0) const = 0;
};

/**
\brief  A criterion for the norm of the gradient of a function to be zero
*/
class CriterionGradNorm :public Criterion {
public:
	CriterionGradNorm(double epsilon = 0.001, int stopId = 10000) :
		Criterion(epsilon, stopId) {};
	virtual const bool stop(vector<double>, const  vector<double>&, Function&,
		int, int = 0)  const override;
};

/**
\brief Criterion for exceeding the agreed number of iterations
*/
class CriterionNumOfIteration :public Criterion {
public:
	CriterionNumOfIteration(int stopId = 10000, double epsilon = 0.001) :
		Criterion(epsilon, stopId) {};
	virtual const bool stop(vector<double> x, const vector<double>& y,
		Function& f, int nIteration, int nIterationWithoutChange = 0) const override;
};

/**
\brief A criterion for exceeding the agreed number of iterative iterations.
*/
class CriterionNumOfNochangeIteration :public Criterion {
	int stopIfnoChange;
public:
	CriterionNumOfNochangeIteration(int N = 1000, double epsilon = 0.001,
		int stopId = 10000) :Criterion(epsilon, stopId), stopIfnoChange(N) {};
	virtual const bool stop(vector<double> x, const vector<double>& y,
		Function& f, int nIteration, int nIterationWithoutChange) const override;
};

/**
\brief A criterion of the proximity to zero of the modulus of the difference between the values of a function of two successive points of an iterative sequence.
*/
class CriterionDifferenceOfValuef : public Criterion {
public:
	CriterionDifferenceOfValuef(double epsilon = 0.001, int stopId = 10000) :
		Criterion(epsilon, stopId) {};
	virtual const bool stop(vector<double> x, const  vector<double>& y,
		Function& f, int nIteration, int nIterationWithoutChange = 0) const override;
};
/**
\brief Criterion for the closeness of the norm to zero
Introduced for one-dimensional quantities
*/
class CriterionOneDimNorm :public Criterion {
public:
	CriterionOneDimNorm(double epsilon = 0.001, int stopId = 10000) :
		Criterion(epsilon, stopId) {};
	virtual const bool stop(vector<double> x, const vector<double>& y,
		Function& f, int nIteration, int nIterationWithoutChange = 0) const override;
};