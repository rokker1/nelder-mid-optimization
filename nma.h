#ifndef NMA_H
#define NMA_H

#include <fstream>
#include "types.h"

#define EPS 1e-4

struct FnValuePair {
	unsigned idx;
	double fn_value;
	
	FnValuePair(unsigned idx, double fn_value);
};

// Nelder-Mid Algorithm
class NMA {
private:
	PointsVector points_;
	TargetFn target_fn_;
	std::ofstream& output_file_;
public:
	NMA(PointsVector& points, TargetFn fn, std::ofstream& output_file);
	
	Point GravityCenterExceptPoint(unsigned idx);
	
	void PrintSimplexToConsole();
	
	void GnuplotizeSimplex();
	
	double CountFnValue(Point& p);
	
	double CountFnValue(unsigned idx);
	
	double CountSigma();
	
	void Run();
};

#endif
