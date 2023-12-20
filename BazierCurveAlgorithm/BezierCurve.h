#pragma once
#include "pch.h"
#include "Point.h"
#include<vector>

using namespace std;
class BAZIERCURVEALGORITHM_API Bezier
{
public:
	Bezier(Point inP0, Point inP1, Point inP2, Point inP3);
	~Bezier();

	void drawCurve(Point inP0, Point inP1, Point inP2, Point inP3, vector<float>& mVertices, vector<float>& mColors);

private:
	Point mP0;
	Point mP1;
	Point mP2;
	Point mP3;

	float blend1;
	float blend2;
	float blend3;
	float blend4;
};
