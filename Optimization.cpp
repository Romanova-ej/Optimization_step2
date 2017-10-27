#include "HArea.h"
#include "HCriterion.h"
#include "HFunction.h"
#include "HOptimization.h"
using namespace std;
//double eps = 0.001;

mt19937 mt_rand(time(0));//time(0)
uniform_real_distribution<>u(0, 1);

const char* Fletcher_Rivs::get_method_name() const { return "Fletcher Rivs method"; }
double Fletcher_Rivs::find_border_alpha(vector<double>& x, Area& D) {
	double border = forBORDER;//или первый вынести из цикла
	double temp = forBORDER;
	for (int i = 0; i < x.size(); ++i) {
		if (p[i] > 0) temp = (D.get_right()[i] - x[i]) / p[i];
		if (p[i] < 0) temp = (D.get_left()[i] - x[i]) / p[i];
		if (abs(temp) < border) border = abs(temp);
	}
	return border;
}
vector<double> Fletcher_Rivs::minimize( vector<double> x, Function& f, Area& D, Criterion& c1, Criterion& c2) {//x -- наачльная точка
	double b = 0; double a = 1;//////////ВАЖНО: Здесь с1 -- критерий нормы градиента, в который мы засунули свою точность эпсилон. тут в аргмине точность должна быть такая же. если меняем критерий, то с1 все равно должен быть с эпсилон
//иначе можно брать минимум из эпсилон в критериях, если оба не зависят от эпсилон, то берется по умолчанию. или передавать отдельно точность
	//попробуем создавать тут эпислон такое, чтобы работало
	double epsilon_for_argmin = c1.get_eps() < c2.get_eps() ? c1.get_eps() : c2.get_eps();//<=0.001
	vector<double> r0(f.grad(x));
	vector<double> x0(x);////////для нормальной работы критериев произвольных
	p = (-1)*r0;
	vector<double> r(x.size());
  
	for (int k = 0; !c1.stop(x,x0, f, k) && !c2.stop(x,x0, f, k) && a; ++k) {
		x0 = x;
		a = argmin(x, f, D,epsilon_for_argmin);
		x = x + a*p;
		r = f.grad(x);
		b = scalar_prod(r, r) / scalar_prod(r0, r0);
		p = (-1)*r + b*p;
		r0 = r;
		newiteration();
	}
	return x;
}
double Fletcher_Rivs::argmin(vector<double> x, Function& f, Area& D,double argmineps) {
	double l = 0, r = find_border_alpha(x, D);
	double m = (l + r) / 2;
	Criterion_one_dim_norm c(argmineps*0.1);
	while (!c.stop(vector<double> (1,f.directional_derivative(x + m*p, p)),x,f,0)) {
		//while (abs(f.directional_derivative(x + m*p, p)) >= 0.00001){
//	while (abs(f.directional_derivative(x + m*p, p)) >= 0.0001) {//быстрее всех(иногда циклится)//здесь конкретный критерий всегда, это внутренность, я сама выбираю
		if (f.directional_derivative(x + m*p, p) > 0)
			r = m;
		else l = m;
		m = (l + r) / 2;
	}
	return m;
}



vector<double> Random_Search::Uni_in_D(Area& D) {
	int dim = D.get_left().size();
	vector<double> randx;
	for (int k = 0; k < dim; ++k) {
		randx.push_back(D.get_left()[k] + (D.get_right()[k] - D.get_left()[k])*u(mt_rand));
	}
	return randx;
}
Random_Search::Random_Search(double probability, int whenSTOP, double whatchange) :p(probability), STOPif_no_change(whenSTOP), change(whatchange) {
	radius = 4;// initial_radius(D);
	radius_change = radius;
}
double Random_Search::initial_radius(Area& D) const {
	double mind = 0;
	for (int i = 0; i < D.get_dim(); ++i) {
		double temp = D.get_right()[i] - D.get_left()[i];
		mind = mind > temp ? temp : mind;
	}
	return mind;
}
const char* Random_Search::get_method_name() const { return "Random Search"; }
vector<double> Random_Search::minimize( vector<double> x, Function& f, Area& D, Criterion& c1, Criterion& c2) {//мь перед x &
	int dim = f.get_dim();
	vector<double>y(dim);
	vector<double>y0(dim);
	vector<double> leftB(dim);
	vector<double> rightB(dim);
	bool flag;
	x = Uni_in_D(D);
	y = x;
	for (int i = 0, no_change = 0; !c1.stop(y,y0,f,i,no_change) && !c2.stop(y,y0,f,i,no_change); ++i) {//второй критерий все-таки хотелось бы как-то вынести
		if (u(mt_rand) < p) {//генерируем х
			x = Uni_in_D(D);
			flag = true;
		}
		else {
			for (int k = 0; k < dim; ++k) {
				leftB[k] = y[k] - radius_change > D.get_left()[k] ? y[k] - radius_change : D.get_left()[k];
				rightB[k] = y[k] + radius_change < D.get_right()[k] ? y[k] + radius_change : D.get_right()[k];
			}
			Area B(leftB, rightB);
			x = Uni_in_D(B);
			radius_change *= change;
			flag = false;
		}
		if (f(y) > f(x)) {
			y0 = y;
			y = x;
			no_change = 0;
			if (flag) radius_change = radius;
		}
		else ++no_change;
		newiteration();
	}
	return y;
}



