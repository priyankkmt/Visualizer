#include "pch.h"
#include "Hermite.h"
#include "Point.h"

Hermite::Hermite(Point inP0, Point inP1, Point inP2, Point inP3) :
    mP0(inP0),
    mP1(inP1),
    mP2(inP2),
    mP3(inP2)
{

}
Hermite::~Hermite()
{

}

void Hermite::drawCurve(Point inP0, Point inP1, Point inP2, Point inP3, vector<float>& mVertices, vector<float>& mColors)
{
    float t;
    float t2;
    float t3;
    for (t = 0; t <= 1; t += 0.001)
    {
        t2 = t * t;
        t3 = t2 * t;

        blend1 = (2 * t3) - (3 * t2) + 1;
        blend2 = (-2 * t3) + (3 * t2);
        blend3 = t3 - (2 * t2) + t;
        blend4 = t3 - t2;

        float x = blend1 * inP0.x() + blend2 * (inP1.x() - inP0.x()) + blend3 * inP2.x() + blend4 * (inP3.x() - inP2.x());
        float y = blend1 * inP0.y() + blend2 * (inP1.y() - inP0.y()) + blend3 * inP2.y() + blend4 * (inP3.y() - inP2.y());
        float z = blend1 * inP0.z() + blend2 * (inP1.z() - inP0.z()) + blend3 * inP2.z() + blend4 * (inP3.z() - inP2.z());

        mVertices.push_back(x);
        mVertices.push_back(y);
        mVertices.push_back(z);


        mColors.push_back(0.0f);
        mColors.push_back(1.0f);
        mColors.push_back(0.0f);

        mVertices.push_back(x);
        mVertices.push_back(y);
        mVertices.push_back(z);

        mColors.push_back(0.0f);
        mColors.push_back(1.0f);
        mColors.push_back(0.0f);
    }
}