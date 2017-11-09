#include "HFunction.h"
#include "HCriterion.h"
using namespace std;


inline const double Criterion::getEps() const { return eps; }
const bool CriterionGradNorm::stop(vector<double> x, const  vector<double>& y,
	Function& f, int nIteration, int nIterationWithoutChange)  const {
	return ((norm(f.getGradient(x)) < getEps()) || 
		stopIfMoreIteration(nIteration));
}
const bool Criterion::stopIfMoreIteration(int nIteration) const {
	return(nIteration > stopIndex);
}

const bool CriterionNumOfIteration::stop(vector<double> x,
	const vector<double>& y, Function& f, int nIteration,
	int nIterationWithoutChange) const
{
	return stopIfMoreIteration(nIteration);
}

const bool CriterionNumOfNochangeIteration::stop(vector<double> x, 
	const vector<double>& y, Function& f, int nIteration, 
	int nIterationWithoutChange) const {
	return((nIterationWithoutChange > stopIfnoChange) || 
		stopIfMoreIteration(nIteration));
}

const bool CriterionDifferenceOfValuef::stop(vector<double> x,
	const  vector<double>& y, Function& f, int nIteration,
	int nIterationWithoutChange) const {
	return((fabs(f(x) - f(y)) < getEps()) || stopIfMoreIteration(nIteration));
}
const bool CriterionOneDimNorm::stop(vector<double> x, const vector<double>& y,
	Function& f, int nIteration, int nIterationWithoutChange) const {
	return((fabs(x[0]) < getEps()) || stopIfMoreIteration(nIteration));
}