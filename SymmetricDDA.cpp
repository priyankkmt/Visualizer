#include "stdafx.h"
#include "SymmetricDDA.h"

SymmetricDDA::SymmetricDDA() {}
SymmetricDDA::~SymmetricDDA() {}

void SymmetricDDA::symmetricDDALinePixels(Line line, QVector<QVector2D>& pixelVertices)
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
        pixelVertices.append(QVector2D(round(x1), round(y1)));
        pixelVertices.append(QVector2D(round(x1) + 1, round(y1)));
        pixelVertices.append(QVector2D(round(x1) + 1, round(y1) + 1));
        pixelVertices.append(QVector2D(round(x1), round(y1) + 1));
        x1 = deltaX + x1;
        y1 = deltaY + y1;
    }
    /*int i = 0;
    while (i < pixelVertices.size())
    {
        QVector<QVector2D> qv;
        qv.append(pixelVertices[i]);
        i++;
        qv.append(pixelVertices[i]);
        i++;
        qv.append(pixelVertices[i]);
        i++;
        qv.append(pixelVertices[i]);
        i++;
        QVector3D fillColor(1.0f, 0.0f, 0.0f);
        openglWindow.fillSquare(qv, fillColor);
    }*/
}