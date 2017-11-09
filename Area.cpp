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
