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
using namespace std;

vector<double> operator+(const vector<double>& a, const vector<double> &b);
const vector<double> operator*(const double a, const vector<double> &B);

double scalar_prod(const vector<double>& a, const vector<double>& b);

double norm(const vector<double>& x);