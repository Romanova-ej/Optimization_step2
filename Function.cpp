#include "HFunction.h"
using namespace std;

void Function::set_dim(const int d) { dim = d; }
int const Function::get_dim() const { return dim; }
Function::~Function() { dim = 0; }
 vector<double> Function::grad(const vector<double>& x)  {
	vector<double> temp(x.size());
	vector<double> ort(x.size());
	for (int i = 0; i < x.size(); ++i) {
		ort[i] = 1;
		temp[i] = (f(x + delta*ort) - f(x + (-delta)*ort)) / (2 * delta);
		ort[i] = 0;
	}
	return temp;
}
double Function::directional_derivative(const vector<double>& x, const vector<double>& p) {//x -- точка, p --направление можно как проекци€ градиента, но лишний раз его считать -- плохо. но если уже считали( а вообще говор€ -- да, то лучше так, если он хранитс€ в лкассе и к нему можно просто обратитьс€)
	return(scalar_prod(grad(x), (1 / norm(p))*p));
	//return((f(x+delta*((1 / norm(p))*p))-f(x+(-1)*delta*((1 / norm(p))*p)))/(2*delta));
}

double Function::operator()(const vector<double>&x) {
	return f(x);
}


fun1::fun1() { set_dim(2); }
const char* fun1::get_function_name() const { return "(x-2)^4+(x-2y)^2"; };
const double fun1::f(const vector<double>& x) {
	return((x[0] - 2)*(x[0] - 2)*(x[0] - 2)*(x[0] - 2) + (x[0] - 2 * x[1])*(x[0] - 2 * x[1]));
}




fun2::fun2() { set_dim(4); }
const double fun2::f(const vector<double>& x) {
	return(x[0] * x[0] + x[1] * x[1] + x[3] * x[3] + x[2] * x[2]);
}
vector<double> fun2::grad(const vector<double>& x) {//тут пусть дана €вно
	return 2 * x;
}
const char* fun2::get_function_name() const { return"x1^2+x2^2+x3^2+x4^2"; }

fun3::fun3() { set_dim(2); }
const double fun3::f(const vector<double>& x) {//прост квадратична€  решени€: x1=2x2,  f=0;
	return((x[0] - 2 * x[1])*(x[0] - 2 * x[1]));
}
const char* fun3::get_function_name() const { return"(x1-2x2)^2"; }


fun4::fun4() { set_dim(2); }// решени€: x=(1,1),  f=0;
const char* fun4::get_function_name() const { return "(x2-x1^2)^2+100*(1-x1)^2"; };
	const  double fun4::f(const vector<double>& x) {
		return((x[1] - x[0] * x[0])*(x[1] - x[0] * x[0]) + 100 * (1 - x[0])*(1 - x[0]));
	}


	fun5::fun5() { set_dim(4); }// //функци€ є7 x=(0,0,0,0), f=0;
	const char* fun5::get_function_name() const { return "(x1+10x2)^2+5(x3-x4)^2+(x2-2x3)^4+10(x1-x4)^4"; };
	const  double fun5::f(const vector<double>& x) {
		return((x[0] + 10 * x[1])*(x[0] + 10 * x[1]) + 5 * pow(x[2] - x[3], 2) + pow(x[1] - 2 * x[2], 4) + 10 * pow(x[0] - x[3], 4));
	}

