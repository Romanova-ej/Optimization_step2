// Optimization_step2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <iomanip>
#include<random>
using namespace std;
const double eps = 0.001;
const double delta = 0.000000001;
const int STOPindex = 100000 ;
const int forBORDER = 1000000;
mt19937 mt_rand(time(0));
uniform_real_distribution<>u(0, 1);

class Function {
	int dim;
public:
	void set_dim(int d) { dim = d; }
    int const get_dim() const { return dim; }
	virtual double f(vector<double>) = 0;
	~Function() { dim=0; }
	virtual const char* get_function_name() const = 0;
	virtual vector<double> grad(const vector<double>& x) {
		vector<double> temp(x.size());
		vector<double> ort(x.size());
		for (int i = 0; i < x.size(); ++i) {
			ort[i] = 1;
			temp[i] = (f(x + delta*ort) - f(x + (-delta)*ort)) / (2 * delta);
			ort[i] = 0;
		}
		return temp;
	}
	double directional_derivative(vector<double> x, vector<double> p) {//x -- точка, p --направление можно как проекция градиента, но лишний раз его считать -- плохо. но если уже считали( а вообще говоря -- да, то лучше так, если он хранится в лкассе и к нему можно просто обратиться)
		return(scalar_prod(grad(x), (1 / norm(p))*p));
		//return((f(x+delta*((1 / norm(p))*p))-f(x+(-1)*delta*((1 / norm(p))*p)))/(2*delta));
	}
	friend double norm(vector<double>& x);
	friend double scalar_prod(vector<double> a, vector<double> b);
	friend const vector<double> operator*(const double a, const vector<double> &B);
	friend vector<double> operator+(const vector<double>& a, const vector<double> &b);
};
class fun1 :public Function {
public:
	fun1() { set_dim(2); }
	virtual const char* get_function_name() const override { return "(x-2)^4+(x-2y)^2"; };
	virtual double f(vector<double> x) override {
		return((x[0] - 2)*(x[0] - 2)*(x[0] - 2)*(x[0] - 2) + (x[0] - 2 * x[1])*(x[0] - 2 * x[1]));}
};


class fun2 :public Function {
public:
	fun2() { set_dim(4); }
	virtual double f(vector<double> x) override {
		return(x[0] * x[0] + x[1] * x[1] + x[3] * x[3] + x[2] * x[2]);}
	virtual vector<double> grad(const vector<double>& x) {//тут пусть дана явно
		return 2 * x;}	
	virtual const char* get_function_name() const override { return"x1^2+x2^2+x3^2+x4^2"; }
};

class Criterion {//везде в методах добавить !
public:
	virtual const bool stop(vector<double> x, Function& f,int num_iteration) const = 0;
};

class Criterion_grad_norm :public Criterion {
public:
	virtual const bool stop(vector<double> x, Function& f, int num_iteration)  const override {
		return (norm(f.grad(x)) < eps);
	}
};

class Criterion_num_of_iteration :public Criterion {
public:
	virtual const bool stop(vector<double> x, Function& f, int num_iteration) const override {
		return(num_iteration > STOPindex);
	}
};

//class Criterion_f_norm : public Criterion {
//public:
//	virtual bool stop(vector<double> x, Function& f, int num_iteration) override {
//		return abs(f.f(y) - f(y0))>eps
//	}
//};

class Area{
	vector<double> left;
	vector<double> right;
	int dim;
public:
	Area(vector<double>l, vector<double> r) : left(l), right(r), dim(l.size()) {}
	Area() : dim(0) {}
	void set_area(vector<double> l, vector<double> r) {
		left = l;
		right = r;
		dim = l.size();
	}
	const int get_dim()const {
		//dim= left.size();
		return dim;
	}
	const vector<double> get_left() const {
		return left;
	}
	const vector<double> get_right()const {
		return right;
	}
};

class Area_dim4 :public Area {
public:
	Area_dim4() {
		double l[4] = { -4,-4,-4,-4 };
		double r[4] = { 2,2,2,2 };
		vector<double> leftD(l, l + 4);
		vector<double> rightD(r, r + 4);
		set_area(leftD, rightD);
	}
};

class Area_dim2 : public Area {
public:
	Area_dim2() {
		double l[2] = { -1,-1 };
		double r[2] = { 2,2};
		vector<double> leftD(l, l +2);
		vector<double> rightD(r, r + 2);
		set_area(leftD, rightD);
	}
};

class Optimization {
	int counter=0;
public:
	virtual vector<double> minimize(vector<double> x, Function& f, Area& D, Criterion& c1, Criterion& c2) = 0;
	virtual const char* get_method_name() const = 0;
	int get_counter() { return counter; }
	void newiteration () { ++counter; }
};

class  Fletcher_Rivs :public Optimization {
	vector<double> p;
public:
	virtual const char* get_method_name() const { return "Fletcher Rivs method"; }
	double find_border_alpha(vector<double>& x, Area& D) {
		double border = forBORDER;//или первый вынести из цикла
		double temp = forBORDER;
		for (int i = 0; i < x.size(); ++i) {
			if (p[i] > 0) temp = (D.get_right()[i] - x[i]) / p[i];
			if (p[i] < 0) temp = (D.get_left()[i] - x[i]) / p[i];
			if (abs(temp) < border) border = abs(temp);
		}
		return border;
	}
	virtual vector<double> minimize(vector<double> x,Function& f, Area& D,Criterion& c1, Criterion& c2) override{//x -- наачльная точка
		double b = 0; double a = 1;
		vector<double> r0(f.grad(x));
		 p=(-1)*r0;
		vector<double> r(x.size());
		for (int k = 0; !c1.stop(x,f,k) && !c2.stop(x,f,k) && a; ++k) {
			a = argmin(x, f,D);
			x = x + a*p;
			r = f.grad(x);
			b = scalar_prod(r,r) / scalar_prod(r0,r0);
			p = (-1)*r + b*p;
			r0 = r;
			newiteration();
		}
		return x;
	}
	double argmin(vector<double> x, Function& f,Area& D) {
		double l = 0, r = find_border_alpha(x, D);
		double m = (l + r) / 2;
		while (abs(f.directional_derivative(x + m*p, p)) >= eps) {//быстрее всех(иногда циклится)
			if (f.directional_derivative(x + m*p, p) > 0)
				r = m;
			else l = m;
			m = (l + r) / 2;
		}
		return m;
	}
};

class Random_Search: public Optimization {
	int STOPif_no_change = 1000;
	double p = 0.8;//для бернулли
	double radius = 4;//начальный радиус. мб вычислять в зависимости от D
	double radius_change = radius;//изменяющаяся эпсилон при попадании в один и тот же шар
	double change = 0.8;//множитель изменения радиуса

	vector<double> Uni_in_D(Area& D) {
		int dim = D.get_left().size();
		vector<double> randx;
		for (int k = 0; k < dim; ++k) {
			randx.push_back(D.get_left()[k] + (D.get_right()[k] - D.get_left()[k])*u(mt_rand));
		}
		return randx;
	}
public:
	Random_Search(double probability=0.8, int whenSTOP=1000, double whatchange=0.8) :p(probability), STOPif_no_change(whenSTOP), change(whatchange) {
		radius = 4;// initial_radius(D);
		radius_change = radius;
	}
	double initial_radius(Area& D) const {
		double mind = 0;
		for (int i = 0; i < D.get_dim(); ++i) {
			double temp = D.get_right()[i] - D.get_left()[i];
			mind = mind > temp ? temp : mind;
		}
		return mind;
	}
	virtual const char* get_method_name() const { return "Random Search"; }
	virtual vector<double> minimize(vector<double> x, Function& f, Area& D, Criterion& c1, Criterion& c2) override {//мь перед x &
		int dim = f.get_dim();
		vector<double>y(dim);
		vector<double>y0(dim);
		vector<double> leftB(dim);
		vector<double> rightB(dim);
		bool flag;
		x = Uni_in_D(D);
		y = x;
		for (int i = 0, no_change = 0; (no_change<STOPif_no_change) && (abs(f.f(y) - f.f(y0))>eps); ++i) {//второй критерий все-таки хотелось бы как-то вынести
			if (u(mt_rand) < p) {//генерируем х
				x = Uni_in_D(D);
				flag = true;
			}
			else {
				for (int k = 0; k < dim; ++k) {
					leftB[k] = y[k] - radius_change > D.get_left()[k] ? y[k] - radius_change : D.get_left()[k];
					rightB[k] = y[k] + radius_change < D.get_right()[k] ? y[k] + radius_change : D.get_right()[k];
				}
				Area B(leftB, rightB);
				x = Uni_in_D(B);
				radius_change *= change;
				flag = false;
			}
			if (f.f(y) > f.f(x)) {
				y0 = y;
				y = x;
				no_change = 0;
				if (flag) radius_change = radius;
			}
			else ++no_change;
			newiteration();
		}
		return y;
	}
};




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
	fun1 f1; Criterion_grad_norm change; Criterion_num_of_iteration d;
	vector<double> x(2, 0);
	vector_print(f1.grad(x));
	Area_dim2 D;

	vector_print(D.get_left());
	vector_print(D.get_right());
	cout << endl;
	
	Random_Search h; Fletcher_Rivs s;
	vector<double> res(h.minimize(x, f1, D,change,d));
	vector<double> res1(s.minimize(x, f1, D, change, d));
	cout << "x= " << endl;
	vector_print(res);
	cout << "k= " << h.get_counter() << endl;
	cout << "x= " << endl;

	vector_print(res1);
	cout << "k= " << s.get_counter() << endl;
	system("pause");
	return 0;
}

