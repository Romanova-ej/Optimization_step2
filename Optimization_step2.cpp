// Optimization_step2.cpp : Defines the entry point for the console application.
//

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
#include "HOptimization.h"
using namespace std;

vector<double> operator+(const vector<double>& a, const vector<double> &b) {
	vector<double> temp;
	for (int i = 0; i < a.size(); ++i)
		temp.push_back(a[i] + b[i]);
	return temp;
}

const vector<double> operator*(const double a, const vector<double> &B) {
	vector<double> temp;
	for (int i = 0; i < B.size(); ++i)
		temp.push_back(a*B[i]);
	return temp;
}

void vector_print(vector<double> x)  {
	for (int i = 0; i < x.size(); ++i)
		cout << x[i] << "   ";
	cout << endl;
}

double scalar_prod(vector<double> a, vector<double> b) {
	double sum = 0;
	for (int i = 0; i < a.size(); ++i)
		sum += a[i] * b[i];
	return sum;
}
double norm(vector<double>& x) {
	double temp = 0;
	for (int i = 0; i < x.size(); ++i) {
		if (abs(x[i]) > temp) temp = abs(x[i]);
	}
	return temp;
}


int main()
{
	fun1 f1; 
	Criterion_grad_norm cf(0.00001); Criterion_num_of_iteration df;//эти критерии логично использовать для Флетчера-Ривса
	Criterion_num_of_nochange_iteration cr; Criterion_dif_of_f dr;//эти критерии логично использовать для Случайного поиска. мб все же сделать критерии выхода членами класса оптимизация и по умолчанию прописывать? 
	vector<double> x(2, 0);
	vector_print(f1.grad(x));
	Area_dim2 D;

	vector_print(D.get_left());
	vector_print(D.get_right());
	cout << endl;
	
	Random_Search h; Fletcher_Rivs s;
	vector<double> res(h.minimize(x, f1, D,cr,dr));//случайный
	vector<double> res1(s.minimize(x, f1, D, cf, df));//флетчер
	cout << "x= " << endl;
	vector_print(res);
	cout << "k= " << h.get_counter() << endl;
	cout << "x= " << endl;

	vector_print(res1);
	cout << "k= " << s.get_counter() << endl;
	system("pause");
	return 0;
}

