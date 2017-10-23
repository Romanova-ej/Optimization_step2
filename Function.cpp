#include "HFunction.h"
using namespace std;

void Function::set_dim(int d) { dim = d; }
int const Function::get_dim() const { return dim; }
Function::~Function() { dim = 0; }
vector<double> Function::grad(const vector<double>& x) {
	vector<double> temp(x.size());
	vector<double> ort(x.size());
	for (int i = 0; i < x.size(); ++i) {
		ort[i] = 1;
		temp[i] = (f(x + delta*ort) - f(x + (-delta)*ort)) / (2 * delta);
		ort[i] = 0;
	}
	return temp;
}
double Function::directional_derivative(vector<double> x, vector<double> p) {//x -- точка, p --направление можно как проекция градиента, но лишний раз его считать -- плохо. но если уже считали( а вообще говоря -- да, то лучше так, если он хранится в лкассе и к нему можно просто обратиться)
	return(scalar_prod(grad(x), (1 / norm(p))*p));
	//return((f(x+delta*((1 / norm(p))*p))-f(x+(-1)*delta*((1 / norm(p))*p)))/(2*delta));
}


fun1::fun1() { set_dim(2); }
const char* fun1::get_function_name() const { return "(x-2)^4+(x-2y)^2"; };
double fun1::f(vector<double> x) {
	return((x[0] - 2)*(x[0] - 2)*(x[0] - 2)*(x[0] - 2) + (x[0] - 2 * x[1])*(x[0] - 2 * x[1]));
}




fun2::fun2() { set_dim(4); }
double fun2::f(vector<double> x) {
	return(x[0] * x[0] + x[1] * x[1] + x[3] * x[3] + x[2] * x[2]);
}
vector<double> fun2::grad(const vector<double>& x) {//тут пусть дана явно
	return 2 * x;
}
const char* fun2::get_function_name() const { return"x1^2+x2^2+x3^2+x4^2"; }
