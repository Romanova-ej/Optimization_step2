#include "HFunction.h"
#include "HCriterion.h"
#include"Hother.h"
using namespace std;


inline const double Criterion::getEps() const {
	return eps; }
const bool CriterionGradNorm::stop(const vector<double>& x, 
	const  vector<double>& y,
	const Function& f, int nIteration, int nIterationWithoutChange)  const {
	return ((norm(f.getGradient(x)) < getEps()) || 
		stopIfMoreIteration(nIteration));
}
const bool Criterion::stopIfMoreIteration(int nIteration) const {
	return(nIteration > stopIndex);
}

const bool CriterionNumOfIteration::stop(const vector<double>& x,
	const vector<double>& y, const Function& f, int nIteration,
	int nIterationWithoutChange) const
{
	return stopIfMoreIteration(nIteration);
}

const bool CriterionNumOfNochangeIteration::stop(const vector<double>& x,
	const vector<double>& y, const Function& f, int nIteration,
	int nIterationWithoutChange) const {
	return((nIterationWithoutChange > stopIfnoChange) || 
		stopIfMoreIteration(nIteration));
}

const bool CriterionDifferenceOfValuef::stop(const vector<double>& x,
	const  vector<double>& y, const Function& f, int nIteration,
	int nIterationWithoutChange) const {
	return((fabs(f.f(x) - f.f(y)) < getEps()) || 
		stopIfMoreIteration(nIteration));
}
const bool CriterionOneDimNorm::stop(const vector<double>& x,
	const vector<double>& y,
	const Function& f, int nIteration, int nIterationWithoutChange) const {
	return((fabs(x[0]) < getEps()) || stopIfMoreIteration(nIteration));
}