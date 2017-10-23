#pragma once
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <iomanip>
#include<random>
using namespace std;

class Area {
	vector<double> left;
	vector<double> right;
	int dim;
public:
	Area(vector<double>l, vector<double> r) : left(l), right(r), dim(l.size()) {}
	Area() : dim(0) {}
	void set_area(vector<double> l, vector<double> r);
	const int get_dim()const;
	const vector<double> get_left() const;
	const vector<double> get_right()const;
};

class Area_dim4 :public Area {
public:
	Area_dim4();
};

class Area_dim2 : public Area {
public:
	Area_dim2(); 
};