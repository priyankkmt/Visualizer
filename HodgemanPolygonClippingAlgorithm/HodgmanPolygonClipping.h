#pragma once
#include "shape.h"
#include "pch.h"

class HODGEMANPOLYGONCLIPPINGALGORITHM_API HodgmanPolygonClipping
{
public:
	HodgmanPolygonClipping(Shape& region, Shape& polygon);
	~HodgmanPolygonClipping();
	Shape getClippedPolygon();
	//void setPolygon(Shape polygon);

private:
	void clipAlongLine(Line l);
	double xIntersect(Line l1, Line l2);
	double yIntersect(Line l1, Line l2);

private:
	Shape mPolygon;
	Shape mRegion;
};