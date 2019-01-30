#include <vector>
#include <cmath>
#include <iostream>
#include "nma.h"

using namespace std;

FnValuePair::FnValuePair(unsigned idx, double fn_value) :
	idx(idx),
	fn_value(fn_value) {}

bool
CompareFnValuePairs(FnValuePair fvp1, FnValuePair fvp2) {
	return (fvp1.fn_value > fvp2.fn_value);
}

NMA::NMA(PointsVector& points, TargetFn target_fn, ofstream& output_file) :
	output_file_(output_file),
	points_(points) {
	target_fn_ = target_fn;
}

Point
NMA::GravityCenterExceptPoint(unsigned idx) {
	Point sum = points_[!idx ? 1 : 0];
	for (unsigned i(1); i < points_.size(); i++)
		if (i != idx)
			sum = sum + points_[i];
	
	return sum * (1.0 / (points_.size() - 1));
}

double
NMA::CountFnValue(Point& p) {
	return (*target_fn_)(p);
}

double
NMA::CountFnValue(unsigned index) {
	return (*target_fn_)(points_[index]);
}

void
NMA::PrintSimplexToConsole() {
	for (auto point : points_) {
		cout << "(";
		for (unsigned i(0); i < point.Size(); i++) {
			cout << point.At(i) << (i < point.Size() - 1 ? "; " : "");
		}
		cout << ")" << endl;
	}
	cout << endl;
}

void
NMA::Run() {
	vector<FnValuePair> fn_value_pairs;
	unsigned h_idx, l_idx;
	double f_h, f_g, f_l, f_r, f_e, f_c;
	Point x_0, x_r, x_e, x_c, x_l;
	
	bool stop_flag = false;
	
//	PrintSimplexToConsole();
	GnuplotizeSimplex();
	
	while (!stop_flag) {
		fn_value_pairs.clear();
		
		for (unsigned i(0); i < points_.size(); i++)
			fn_value_pairs.emplace_back(i, CountFnValue(i));
		
		sort(fn_value_pairs.begin(), fn_value_pairs.end(), CompareFnValuePairs);
		
		h_idx = fn_value_pairs[0].idx;
		l_idx = fn_value_pairs[fn_value_pairs.size() - 1].idx;
		
		x_0 = GravityCenterExceptPoint(h_idx);
		x_r = Reflect(points_[h_idx], x_0);
		x_l = points_[l_idx];
		
		f_h = fn_value_pairs[0].fn_value;
		f_g = fn_value_pairs[1].fn_value;
		f_l = fn_value_pairs[fn_value_pairs.size() - 1].fn_value;
		f_r = CountFnValue(x_r);
		
		if (f_r < f_l) {
			x_e = Stretch(x_r, x_0);
			f_e = CountFnValue(x_e);
			
			if (f_e < f_l) {
				points_[h_idx] = x_e;
			} else {
				points_[h_idx] = x_r;
			}
		} else {
			if (f_r < f_g) {
				points_[h_idx] = x_r;
			} else {
				if (f_r < f_h) {
					points_[h_idx] = x_r;
					f_h = f_r;
				}
				
				x_c = Compress(x_r, x_0);
				f_c = CountFnValue(x_c);
				
				if (f_c < f_h) {
					points_[h_idx] = x_c;
				} else {
					for (unsigned i(0); i < points_.size(); i++)
						if (i != l_idx)
							points_[i] = x_l + (points_[i] + (x_l * -1.0)) * 0.5;
				}
			}
		}
		
//		PrintSimplexToConsole();
		GnuplotizeSimplex();
		
		cout << "Sigma = " << CountSigma() << endl;
		
		if (CountSigma() < EPS)
			stop_flag = true;
	}
}

double
NMA::CountSigma() {
	double f_(0), sigma_quad(0), n;
	
	n = points_.size();
	
	for (auto point : points_)
		f_ += CountFnValue(point);
	
	f_ /= n;
	
	for (auto point : points_)
		sigma_quad += pow(CountFnValue(point) - f_, 2.0);
	
	sigma_quad /= n;
	
	return sqrt(sigma_quad);
}

void
NMA::GnuplotizeSimplex() {
	for (auto point : points_) {
		for (unsigned i(0); i < point.Size(); i++)
			output_file_ << point.At(i) << '\t';
			
		output_file_ << CountFnValue(point) << endl;
	}
	// For gnuplot repeating the first element
	for (unsigned i(0); i < points_[0].Size(); i++)
		output_file_ << points_[0].At(i) << '\t';
	
	output_file_ << CountFnValue(points_[0]) << endl << endl << endl;
}



