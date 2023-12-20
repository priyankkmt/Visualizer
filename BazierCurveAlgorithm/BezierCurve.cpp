#include "pch.h"
#include "Bazier.h"
#include "Point.h"

#include <vector>

Bazier::Bazier()
{
    return;
}

Bazier::Bazier(std::vector<Point> points) : mControlPoints(points)
{
}

Bazier::~Bazier()
{
}

void Bazier::calculateBazier(floatVector& mVertices, floatVector& mColors)
{
    for (double t = 0; t <= 1; t += 0.1) {
        Point r = evaluateBazier(t);
        mVertices.push_back(r.x());
        mVertices.push_back(r.y());

        mColors.push_back(1.0f);
        mColors.push_back(1.0f);
        mColors.push_back(0.0f);
    }
    for (int i = 2; i < mVertices.size(); i += 4)
    {
        mVertices.push_back(mVertices[i]);
        mVertices.push_back(mVertices[i + 1]);

        mVertices.push_back(mVertices[i + 2]);
        mVertices.push_back(mVertices[i + 3]);

        mColors.push_back(1.0f);
        mColors.push_back(1.0f);
        mColors.push_back(0.0f);

        mColors.push_back(1.0f);
        mColors.push_back(1.0f);
        mColors.push_back(0.0f);
    }
}

Point Bazier::evaluateBazier(double t)
{
    double u = 1.0 - t;
    double tt = t * t;
    double uu = u * u;
    double uuu = uu * u;
    double ttt = tt * t;

    double x = uuu * mControlPoints[0].x() + 3 * uu * t * mControlPoints[1].x() + 3 * u * tt * mControlPoints[2].x() + ttt * mControlPoints[3].x();
    double y = uuu * mControlPoints[0].y() + 3 * uu * t * mControlPoints[1].y() + 3 * u * tt * mControlPoints[2].y() + ttt * mControlPoints[3].y();
    Point p(x, y);

    return p;
}
