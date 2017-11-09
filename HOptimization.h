#pragma once
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <iomanip>
#include<random>
#include "HArea.h"
#include "HCriterion.h"
#include "HFunction.h"
using namespace std;
/**
\file
\brief Header file describing the class Optimization and its heirs
*/

/**
\brief Abstract class for solve the problem of multidimensional optimization
*/
class Optimization {
	int counter = 0;
public:
	/**
	\brief It finds a minimum point with given parameters
	\param[in] x starting point
	\param[in] f objective function
	\param[in] c1 break criterion
	\return approximation of the vector x on which the objective function reaches a minimum
	*/
	virtual vector<double> minimize(vector<double> x, Function& f,
		Criterion& c) = 0;
	virtual const char* getMethodName() const = 0;
	int getCounter() const { return counter; }
	void newIteration() { ++counter; }
};

/**
\brief The class implements the Fletcher-Reeves method
*/
class  FletcherRivs :public Optimization {
	const int FOR_BORDER = 1000000;
	vector<double> p;
public:
	virtual const char* getMethodName() const;
	const double findBorderAlpha(const vector<double>& x, Area& D) const;
	virtual vector<double> minimize(vector<double> x, Function& f,
		Criterion& c) override;
	double calculateArgmin(vector<double> x, Function& f, double) const;
};

/**
\brief The class implements the random search method
*/
class RandomSearch : public Optimization {
	int stopIfnoChange;
	double p;
	double radius;
	double radiusChange;
	double change;
	vector<double> simulateUniformInD(Area& D);
public:
	RandomSearch(Area& D, double probability = 0.8, int whenStop = 1000,
		double whatChange = 0.9);
	double initializeRadius(Area& D) const;
	virtual const char* getMethodName() const;
	virtual vector<double> minimize(vector<double> x, Function& f,
		Criterion& c) override;
};


