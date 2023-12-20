#include "pch.h"
#include "SymmetricDDA.h"

SymmetricDDA::SymmetricDDA() {}
SymmetricDDA::~SymmetricDDA() {}

void SymmetricDDA::symmetricDDALinePixels(Line line, vectorOfVectorFLoat& pixelVertices)
{
    float x1 = line.p1().x();
    float y1 = line.p1().y();
    float x2 = line.p2().x();
    float y2 = line.p2().y();

    float dx = abs(x2 - x1);
    float dy = abs(y2 - y1);

    float deltaX;
    float deltaY;

    if (dy > dx)
    {
        deltaX = dx / dy;
        deltaY = dy / dy;
    }
    else
    {
        deltaX = dx / dx;
        deltaY = dy / dx;
    }
    while (x1 < x2)
    {
        pixelVertices.push_back(std::vector<float>{(float)round(x1), (float)round(y1)});
        pixelVertices.push_back(std::vector<float>{(float)round(x1) + 1, (float)round(y1)});
        pixelVertices.push_back(std::vector<float>{(float)round(x1) + 1, (float)round(y1) + 1});
        pixelVertices.push_back(std::vector<float>{(float)round(x1), (float)round(y1) + 1});
        x1 = deltaX + x1;
        y1 = deltaY + y1;
    }
}