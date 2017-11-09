#include "HArea.h"
using namespace std;

void Area::setArea(const vector<double>& l, const  vector<double>& r) {
	left = l;
	right = r;
	dim = l.size();
}
const int Area::getDim()const {
	return dim;
}
const vector<double> Area::getLeft() const {
	return left;
}
const vector<double> Area::getRight()const {
	return right;
}

AreaDim4::AreaDim4() {
	double l[4] = { -4,-4,-4,-4 };
	double r[4] = { 2,2,2,2 };
	vector<double> leftD(l, l + 4);
	vector<double> rightD(r, r + 4);
	setArea(leftD, rightD);
}

AreaDim2::AreaDim2() {
	double l[2] = { -1,-1 };
	double r[2] = { 2,2 };
	vector<double> leftD(l, l + 2);
	vector<double> rightD(r, r + 2);
	setArea(leftD, rightD);
}
