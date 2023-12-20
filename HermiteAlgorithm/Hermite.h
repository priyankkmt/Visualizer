#pragma once
#include <vector>
#include "Point.h"
#include "pch.h"
using namespace std;

class HERMITEALGORITHM_API Hermite
{
public:
	Hermite(Point inP0, Point inP1, Point inP2, Point inP3);
	~Hermite();

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

