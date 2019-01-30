#include <algorithm>
#include <iterator>
#include "point.h"

using namespace std;

Point::Point() = default;

Point::Point(vector<double> x) : x_(x) {}

Point::Point(double x, double y) {
	x_ = {x, y};
}

double
Point::Size() {
	return x_.size();
}

double
Point::At(unsigned idx) {
	return x_[idx];
}

Point
Point::operator+(double a) {
	vector<double> result;
	
	for (unsigned i(0); i < this->x_.size(); i++)
		result.push_back(this->x_[i] + a);
	
	return Point(result);
}

Point
Point::operator+(const Point& p) {
	vector<double> result;
	
	for (unsigned i(0); i < this->x_.size(); i++)
		result.push_back(this->x_[i] + p.x_[i]);
	
	return Point(result);
}

Point
Point::operator*(double k) {
	vector<double> result;
	
	for (unsigned i(0); i < this->x_.size(); i++)
		result.push_back(this->x_[i] * k);
	
	return Point(result);
}

Point&
Point::operator=(const Point& p) {
	this->x_.clear();
	this->x_ = p.x_;
	return *this;
}

Point
Reflect(Point& p, Point& c) {
	return c * (1 + rfl_coeff) + p * (-rfl_coeff);
}

Point
Stretch(Point& p, Point& c) {
	return p * str_coeff + c * (1 - str_coeff);
}

Point
Compress(Point& p, Point& c) {
	return p * cmp_coeff + c * (1 - cmp_coeff);
}
