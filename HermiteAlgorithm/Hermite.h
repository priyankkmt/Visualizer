#pragma once
#include <vector>
#include "Point.h"
#include "pch.h"
using namespace std;

typedef std::vector<float> floatVector;

class HERMITEALGORITHM_API Hermite{
public:
	Hermite(void);

public:
	Hermite(std::vector<Point> points);
	~Hermite();
	void calculateHermite(floatVector& mVertices, floatVector& mColors);
private:
	Point evaluateHermite(double t);
private:
	std::vector<Point> mControlPoints;
};
