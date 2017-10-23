#include "HFunction.h"
#include "HCriterion.h"
using namespace std;

const double Criterion::get_eps() const { return eps; }
const bool Criterion_grad_norm::stop(vector<double> x, vector<double> y, Function& f, int num_iteration, int num_iteration_without_change)  const {
	return (norm(f.grad(x)) < get_eps());
}

const bool Criterion_num_of_iteration::stop(vector<double> x, vector<double> y, Function& f, int num_iteration, int num_iteration_without_change) const {
	return(num_iteration > STOPindex);
}

const bool Criterion_num_of_nochange_iteration::stop(vector<double> x, vector<double> y, Function& f, int num_iteration, int num_iteration_without_change) const {
	return(num_iteration_without_change > STOPifno_change);
}

const bool Criterion_dif_of_f::stop(vector<double> x, vector<double> y, Function& f, int num_iteration, int num_iteration_without_change) const {
	return(abs(f.f(x) - f.f(y)) < get_eps());
}
const bool Criterion_one_dim_norm::stop(vector<double> x, vector<double> y, Function& f, int num_iteration, int num_iteration_without_change) const {
	return(abs(x[0])<get_eps());//немного костыль. это для случая константы 
}