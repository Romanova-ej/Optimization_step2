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

void vector_print(vector<double> x) {
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

void printAreaf(Area& D) {
	cout << "[" << D.getLeft()[0] << ";" <<
		D.getRight()[0] << "]";
	for (int i = 1; i < D.getDim(); ++i) {
		cout << "*" << "[" << D.getLeft()[i] << ";" <<
			D.getRight()[i] << "]";
	}
	cout << endl;
}

int main()
{
	std::shared_ptr<Function> f;
	int functionNumber;
	cout << "Select an objective function for optimization" << endl;
	cout << "1. (x-2)^4+(x-2y)^2" << endl << "2. x1^2+x2^2+x3^2+x4^2" << endl
		<< "3. (x1-2x2)^2" << endl << "4. (x2-x1^2)^2+100*(1-x1)^2" << endl
		<< "5. (x1+10x2)^2+5(x3-x4)^2+(x2-2x3)^4+10(x1-x4)^4" << endl;
	cin >> functionNumber;
	switch (functionNumber)
	{
	case 1: {
		f = std::make_shared<Fun1>();
		break;
	}
	case 2: {
		f = std::make_shared<Fun2>();
		break;
	}
	case 3: {
		f = std::make_shared<Fun3>();
		break;
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
		cerr << endl << "no function with this number" << endl;
		break;
	}
	}
	vector<double> x; int ans;
	vector<double> left; vector<double> right;
	cout << "default area: " << endl;
	printAreaf(f->getArea());

	cout << "Do you want to change the area (1--yes, 0-- no)?" << endl;
	cin >> ans;

	if (ans) {
		vector<double> l;
		vector<double> r;
		double temp;
		cout << "Enter left bounds " << endl;
		try {
			for (int i = 0; i < f->getDim(); ++i) {
				cin >> temp;
				l.push_back(temp);
			}
			cout << "Enter right bounds " << endl;
			for (int i = 0; i < f->getDim(); ++i) {
				cin >> temp;
				r.push_back(temp);
				if (temp < l[i]) throw 3;
			}

			Area tempD(l, r);
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
				break;
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
			printAreaf(f->getArea());
		}
		catch (int i) { cerr << "ERROR: you entered an empty area!" << endl; }
	}


	cout << "Enter the starting point within the bounds" << endl;
	cout << endl << "x= ";
	try {
		for (int i = 0; i < f->getDim(); ++i) {
			double a;
			cin >> a;
			if ((a < f->getArea().getLeft()[i]) || (a > f->getArea().getRight()[i])) throw 1;
			x.push_back(a);
		}

		std::shared_ptr<Optimization> opt;
		int methodNumber;
		cout << "Select optimization method" << endl << "1. Fletcher Reeves method"
			<< endl << "2. Random search" << endl;
		cin >> methodNumber;
		switch (methodNumber)
		{
		case 1: {
			opt = std::make_shared<FletcherRivs>();
			break;
		}
		case 2: {
			opt = std::make_shared<RandomSearch>(f->getArea());
			break;
		}
		default: {
			cout << "no method with this number" << endl;
			break;
		}
		}

		std::shared_ptr<Criterion> stopCriterion;
		cout << "Select stop criterion" << endl <<
			"1. Criterion for the norm of the gradient of a function" << endl <<
			"2. Criterion for exceeding the agreed number of iterations" << endl <<
			"3. Criterion for exceeding the agreed number of iterative iterations" << endl
			<< "4. Criterion of modulus of the difference between the values of a function"
			<< endl;
		int criterionNumber;
		cin >> criterionNumber;
		switch (criterionNumber)
		{
		case 1:
		{
			try {
				double epsilon;
				cout << "epsilon = ";
				cin >> epsilon;
				if (epsilon <= 0) throw 2;
				stopCriterion = std::make_shared<CriterionGradNorm>(epsilon);
				//it is logical for Fletcher-Reeves
			}
			catch (int i) { cerr << "ERROR: epsilon must be positive!" << endl; }
			break;
		}
		case 2: {
			int nIteration;
			cout << "quantity of iteration = ";
			cin >> nIteration;
			stopCriterion = std::make_shared<CriterionNumOfIteration>(nIteration);
			break;
		}
		case 3: {
			int nIteration;
			cout << "quantity of iteration = ";
			cin >> nIteration;
			stopCriterion = std::make_shared<CriterionNumOfNochangeIteration>(nIteration);
			//it is logical for random search
			break;
		}
		case 4: {
			try {
				double epsilon;
				cout << "epsilon = ";
				cin >> epsilon;
				if (epsilon <= 0) throw 2;
				stopCriterion = std::make_shared<CriterionDifferenceOfValuef>(epsilon);
			}
			catch (int i) { cerr << "ERROR: epsilon must be positive! " << endl; }
			break;
		}
		default: {
			cout << "no criterion with this number" << endl;
			break;
		}
		}

		vector<double> result(opt->minimize(x, *f, *stopCriterion));
		cout << "x= " << endl;
		vector_print(result);
		cout << "k= " << opt->getCounter() << endl;
	}
	catch (int i) { cerr << "ERROR: starting point does not belong to the area" << endl; }

	system("pause");
	return 0;
}

