#include "pch.h"
#include "Hermite.h"
#include "Point.h"

#include <vector>

Hermite::Hermite()
{
    return;
}

Hermite::Hermite(std::vector<Point> points) : mControlPoints(points)
{
}

Hermite::~Hermite()
{
}

void Hermite::calculateHermite(floatVector& mVertices, floatVector& mColors)
{
    for (double t = 0; t <= 1; t += 0.1) {
        Point r = evaluateHermite(t);
        mVertices.push_back(r.x());
        mVertices.push_back(r.y());

        mColors.push_back(1.0f);
        mColors.push_back(1.0f);
        mColors.push_back(0.0f);
    }
}

Point Hermite::evaluateHermite(double t)
{
    double t2 = t * t;
    double t3 = t2 * t;

    double h1 = 2 * t3 - 3 * t2 + 1;
    double h2 = -2 * t3 + 3 * t2;
    double h3 = t3 - 2 * t2 + t;
    double h4 = t3 - t2;

    double x = h1 * mControlPoints[0].x() + h2 * mControlPoints[1].x() + h3 * mControlPoints[2].x() + h4 * mControlPoints[3].x();
    double y = h1 * mControlPoints[0].y() + h2 * mControlPoints[1].y() + h3 * mControlPoints[2].y() + h4 * mControlPoints[3].y();

    return Point(x, y);
}
