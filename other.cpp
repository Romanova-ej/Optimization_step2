#include "Hother.h"
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