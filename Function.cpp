#include "HFunction.h"
using namespace std;

void Function::setDim(const int d) { dim = d; }
int const Function::getDim() const { return dim; }
Function::~Function() { dim = 0; }

Function::Function(const Area& d) :D(d), dim(d.getDim()) {}

Function::Function() {}

vector<double> Function::getGradient(const vector<double>& x) const {
	vector<double> temp(x.size());
	vector<double> ort(x.size());
	for (int i = 0; i < x.size(); ++i) {
		ort[i] = 1;
		temp[i] = (f(x + DELTA*ort) - f(x + (-DELTA)*ort)) / (2 * DELTA);
		ort[i] = 0;
	}
	return temp;
}

double Function::getDirectionalDerivative(const vector<double>& x,
	const vector<double>& p) const {
	return(scalar_prod(getGradient(x), (1 / norm(p))*p));
}

double Function::operator()(const vector<double>&x) {
	return f(x);
}

Area Function::getArea() const {
	return D;
}

Fun1::Fun1() {
	setDim(2);
	double l[2] = { -1,-1 };
	double r[2] = { 2,2 };
	vector<double> leftD(l, l + 2);
	vector<double> rightD(r, r + 2);
	D.setArea(leftD, rightD);
}

const char* Fun1::getFunctionName() const { return "(x-2)^4+(x-2y)^2"; };

inline const double Fun1::f(const vector<double>& x)  const {
	return((x[0] - 2)*(x[0] - 2)*(x[0] - 2)*(x[0] - 2) + (x[0] - 2 * x[1])*
		(x[0] - 2 * x[1]));
}

Fun2::Fun2() {
	setDim(4);
	double l[4] = { -4,-4,-4,-4 };
	double r[4] = { 2,2,2,2 };
	vector<double> leftD(l, l + 4);
	vector<double> rightD(r, r + 4);
	D.setArea(leftD, rightD);
}

inline const double Fun2::f(const vector<double>& x) const {
	return(x[0] * x[0] + x[1] * x[1] + x[3] * x[3] + x[2] * x[2]);
}

vector<double> Fun2::getGradient(const vector<double>& x) {
	return 2 * x;
}

const char* Fun2::getFunctionName() const { return"x1^2+x2^2+x3^2+x4^2"; }

Fun3::Fun3() {
	setDim(2);
	double l[2] = { -4,-4 };
	double r[2] = { 0,0 };
	vector<double> leftD(l, l + 2);
	vector<double> rightD(r, r + 2);
	D.setArea(leftD, rightD);
}

inline const double Fun3::f(const vector<double>& x) const {//x1=2x2,  f=0;
	return((x[0] - 2 * x[1])*(x[0] - 2 * x[1]));
}

const char* Fun3::getFunctionName() const { return"(x1-2x2)^2"; }

Fun4::Fun4() {// x=(1,1),  f=0;
	setDim(2);
	double l[2] = { -1,-1 };
	double r[2] = { 2,2 };
	vector<double> leftD(l, l + 2);
	vector<double> rightD(r, r + 2);
	D.setArea(leftD, rightD);
}

const char* Fun4::getFunctionName() const {
	return "(x2-x1^2)^2+100*(1-x1)^2";
}

inline const  double Fun4::f(const vector<double>& x) const {
	return((x[1] - x[0] * x[0])*(x[1] - x[0] * x[0]) + 100 * (1 - x[0])*
		(1 - x[0]));
}

Fun5::Fun5() {// x=(0,0,0,0), f=0;
	setDim(4);
	double l[4] = { -4,-4,-4,-4 };
	double r[4] = { 2,2,2,2 };
	vector<double> leftD(l, l + 4);
	vector<double> rightD(r, r + 4);
	D.setArea(leftD, rightD);
}

const char* Fun5::getFunctionName() const {
	return "(x1+10x2)^2+5(x3-x4)^2+(x2-2x3)^4+10(x1-x4)^4";
}

inline const  double Fun5::f(const vector<double>& x)const {
	return((x[0] + 10 * x[1])*(x[0] + 10 * x[1]) + 5 * pow(x[2] - x[3], 2) +
		pow(x[1] - 2 * x[2], 4) + 10 * pow(x[0] - x[3], 4));
}

Fun5::Fun5(const Area& d) :Function(d) {};
Fun4::Fun4(const Area& d) :Function(d) {};
Fun3::Fun3(const Area& d) :Function(d) {};
Fun2::Fun2(const Area& d) :Function(d) {};
Fun1::Fun1(const Area& d) :Function(d) {};
