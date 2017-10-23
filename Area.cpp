#include "HArea.h"
using namespace std;

void Area::set_area(vector<double> l, vector<double> r) {
	left = l;
	right = r;
	dim = l.size();
}
const int Area::get_dim()const {
	return dim;
}
const vector<double> Area::get_left() const {
	return left;
}
const vector<double> Area::get_right()const {
	return right;
}

Area_dim4::Area_dim4() {
	double l[4] = { -4,-4,-4,-4 };
	double r[4] = { 2,2,2,2 };
	vector<double> leftD(l, l + 4);
	vector<double> rightD(r, r + 4);
	set_area(leftD, rightD);
}

Area_dim2::Area_dim2() {
	double l[2] = { -1,-1 };
	double r[2] = { 2,2 };
	vector<double> leftD(l, l + 2);
	vector<double> rightD(r, r + 2);
	set_area(leftD, rightD);
}
