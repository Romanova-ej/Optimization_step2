#pragma once
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <iomanip>
#include<random>
/**
\file
\brief Header file describing the class Area and its heirs
*/

using namespace std;
/**
\brief Abstract base class for areas (parallelepiped) on which the minimum is sought
*/
class Area {
	vector<double> left;
	vector<double> right;
	int dim;
public:
	Area(const vector<double>& l, const vector<double>& r) : left(l), right(r), dim(l.size()) {}
	Area() : dim(0) {}
	void setArea(const vector<double>& l, const vector<double>& r);
	const int getDim()const;
	const vector<double> getLeft() const;
	const vector<double> getRight()const;
};

/**
\brief The class stores a region of dimension 4
*/
class AreaDim4 :public Area {
public:
	AreaDim4();
};

/**
\brief The class stores a region of dimension 2
*/
class AreaDim2 : public Area {
public:
	AreaDim2(); 
};