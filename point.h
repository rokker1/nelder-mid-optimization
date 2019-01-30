#ifndef POINT_H
#define POINT_H

#include <vector>

static const double rfl_coeff = 1.0; // rfl_coeff - reflect coeff
static const double cmp_coeff = 0.5; // cmp_coeff - compress coeff
static const double str_coeff = 2.0; // str_coeff - stretch coeff

class Point {
private:
	std::vector<double> x_;
public:
	Point();
	
	explicit Point(std::vector<double> x);
	
	Point(double x, double y);
	
	double Size();
	
	double At(unsigned idx);
	
	Point operator+(const Point&);
	
	Point operator+(double);
	
	Point operator*(double);
	
	Point& operator=(const Point& p);
};

Point Reflect(Point& p, Point& c);

Point Compress(Point& p, Point& c);

Point Stretch(Point& p, Point& c);

#endif
