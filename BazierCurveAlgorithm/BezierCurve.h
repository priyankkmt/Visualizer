#pragma once
#include "pch.h"
#include "Point.h"
#include<vector>

using namespace std;
typedef std::vector<float> floatVector;

class BAZIERCURVEALGORITHM_API Bazier
{
public:
	Bazier(void);

public:
	Bazier(std::vector<Point> points);
	~Bazier();
	void calculateBazier(floatVector& mVertices, floatVector& mColors);
private:
	Point evaluateBazier(double t);
private:
	std::vector<Point> mControlPoints;
};
