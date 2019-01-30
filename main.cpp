#include <cmath>
#include <iostream>
#include "nma.h"

#define OUTPUT_FILE_NAME "output.dat"

using namespace std;

double ZakharovFn(Point& p) {
	double partA(.0), partB(.0);
	
	for (unsigned i(0); i < p.Size(); i++) {
		partA += p.At(i) * p.At(i);
		partB += i * p.At(i);
	}
	
	return partA + pow(partB, 2) + pow(partB, 4);
}

int main(int argc, char** argv) {
	Point p1(2, 4);
	Point p2(5, 6);
	Point p3(1, -1);
	
	PointsVector pv;
	
	pv.push_back(p1);
	pv.push_back(p2);
	pv.push_back(p3);
	
	ofstream output_file(OUTPUT_FILE_NAME);
	
	NMA nma(pv, &ZakharovFn, output_file);
	nma.Run();
	
	output_file.close();
	return 0;
}