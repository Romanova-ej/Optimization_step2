// Optimization_step2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <iomanip>
#include <random>
#include "HArea.h"
#include "HCriterion.h"
#include "HFunction.h"
#include "HOptimization.h"
#include <memory>
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

double scalar_prod(const vector<double>& a, const vector<double>& b) {
	double sum = 0;
	for (int i = 0; i < a.size(); ++i)
		sum += a[i] * b[i];
	return sum;
}
 double norm(const vector<double>& x) {
	double temp = 0;
	for (int i = 0; i < x.size(); ++i) {
		if (fabs(x[i]) > temp) temp = fabs(x[i]);
	}
	return temp;
}

 void printAreaf(shared_ptr<Function> f) {
	 cout << "[" << f->getArea().getLeft()[0] << ";" << f->getArea().getRight()[0] << "]";
	 for (int i = 1; i < f->getDim(); ++i) {
		 cout << "*" << "[" << f->getArea().getLeft()[i] << ";" << f->getArea().getRight()[i] << "]";
	 }
	 cout << endl;
 }

int main()
{
	std::shared_ptr<Function> f;
	int functionNumber;
	cout << "Select an objective function for optimization" << endl;
	cout << "1. (x-2)^4+(x-2y)^2" << endl << "2. x1^2+x2^2+x3^2+x4^2" << endl << "3. (x1-2x2)^2" << endl << "4. (x2-x1^2)^2+100*(1-x1)^2" << endl << "5. (x1+10x2)^2+5(x3-x4)^2+(x2-2x3)^4+10(x1-x4)^4" << endl;
	cin >> functionNumber;
	switch (functionNumber)
	{
	case 1: {
		f = std::make_shared<Fun1>();
		break;
	}
	case 2: {
		f=std::make_shared<Fun2>();
		break;
	}
	case 3: {
		f=std::make_shared<Fun3>();
	}
	case 4: {
		f = std::make_shared<Fun4>();
		break;
	}
	case 5: {
		f = std::make_shared<Fun5>();
		break;
	}
	default: {
		cerr <<endl<< "no function with this number" << endl;
			break;
	}
	}
	//CriterionGradNorm cf(0.00001,1000);// логично использовать для Флетчера-Ривса
	//CriterionNumOfNochangeIteration cr(1000); // логично использовать для Случайного поиска
	////CriterionDifferenceOfValuef cr(0.001,1000);//замечание: если оставлять значения по умолчанию, то проблемы со ссылкой на это
	vector<double> x; int ans;
	vector<double> left; vector<double> right;
	cout << "default area: " << endl;
	printAreaf(f);

	cout << "Do you want to change the area (1--yes, 0-- no)?" << endl;
	cin >> ans;

	if (ans) {
		vector<double> l;
		vector<double> r;
		double temp;
		cout << "Enter left bounds " << endl;
		for (int i = 0; i < f->getDim(); ++i) {
			cin >> temp;
			l.push_back(temp);
		}
		cout << "Enter right bounds " << endl;
		for (int i = 0; i < f->getDim(); ++i) {
			cin >> temp;
			r.push_back(temp);
		}
		
		Area tempD(l,r);//создали такую область, какую хотим. теперь надо ее запихнуть в функцию
		switch (functionNumber)
		{
		case 1: {
			f = std::make_shared<Fun1>(tempD);
			break;
		}
		case 2: {
			f = std::make_shared<Fun2>(tempD);
			break;
		}
		case 3: {
			f = std::make_shared<Fun3>(tempD);
		}
		case 4: {
			f = std::make_shared<Fun4>(tempD);
			break;
		}
		case 5: {
			f = std::make_shared<Fun5>(tempD);
			break;
		}
		default: {
			cerr << endl << "no function with this number" << endl;
			break;
		}
		}
		cout << "Area: " << endl;
		printAreaf(f);
	}
	

	cout << "Enter the starting point within the bounds" << endl;
	cout << endl << "x= ";
	for (int i = 0; i < f->getDim(); ++i) {
		double a;
		cin >> a;
		x.push_back(a);
	}
	/*FletcherRivs fletcher_opt;
	vector<double> fletch_result(fletcher_opt.minimize(x, f, D, cf));*/
	//cout << "x= " << endl;
	//vector_print(fletch_result);
	//cout << "k= " << fletcher_opt.getCounter() << endl;

	//RandomSearch rand_opt(D);
	//vector<double> rand_result(rand_opt.minimize(x, f1, D, cr));
	//cout << "x= " << endl;
	//vector_print(rand_result);
	//cout << "k= " << rand_opt.getCounter() << endl;
	system("pause");
	return 0;
}

