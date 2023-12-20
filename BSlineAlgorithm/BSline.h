#pragma once
#pragma once
#include "Point.h"
#include "pch.h"

#include <iostream>
#include <vector>

using floatList = std::vector<float>;

class BSLINEALGORITHM_API BSpline {
public:
    BSpline(Point inP0, Point inP1, Point inP2, Point inP3);
    ~BSpline();

    double basisFunction(int i, int k, double t);
    void   evaluate(double t, floatList& mVertices, floatList& mColors);
    void   drawCurveBspline(floatList& mVertices, floatList& mColors);

private:
    std::vector<double> knots;
    std::vector<Point> controlPoints;
    int degree;

    Point mP0;
    Point mP1;
    Point mP2;
    Point mP3;
};

extern BSLINEALGORITHM_API int nBSpline;

BSLINEALGORITHM_API int fnBSpline(void);