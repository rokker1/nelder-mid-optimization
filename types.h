#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include "point.h"

typedef std::vector<Point> PointsVector;

typedef double (*TargetFn)(Point &);

#endif
