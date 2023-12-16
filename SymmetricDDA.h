#pragma once
#include "Line.h"
#include "OpenGLWindow.h"

class SymmetricDDA
{
public:
    SymmetricDDA();
    ~SymmetricDDA();

public:
    void symmetricDDALinePixels(Line line, QVector<QVector2D>& pixelVertices);
};