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



class Optimization {
	int counter = 0;
public:
	virtual vector<double> minimize(vector<double> x, Function& f, Area& D, Criterion& c1, Criterion& c2) = 0;
	virtual const char* get_method_name() const = 0;
	int get_counter() { return counter; }
	void newiteration() { ++counter; }
};

class  Fletcher_Rivs :public Optimization {
	const int forBORDER = 1000000;
	vector<double> p;
public:
	virtual const char* get_method_name() const;
	double find_border_alpha(vector<double>& x, Area& D);
	virtual vector<double> minimize( vector<double> x, Function& f, Area& D, Criterion& c1, Criterion& c2) override;
	double argmin(vector<double> x, Function& f, Area& D,double);
};

class Random_Search : public Optimization {
	int STOPif_no_change;
	double p;//дл€ бернулли
	double radius;//начальный радиус. мб вычисл€ть в зависимости от D
	double radius_change;//измен€юща€с€ эпсилон при попадании в один и тот же шар
	double change;//множитель изменени€ радиуса
	vector<double> Uni_in_D(Area& D);
public:
	Random_Search(double probability = 0.8, int whenSTOP = 1000, double whatchange = 0.8);
	double initial_radius(Area& D) const;
	virtual const char* get_method_name() const;
	virtual vector<double> minimize( vector<double> x, Function& f, Area& D, Criterion& c1, Criterion& c2) override;
};


