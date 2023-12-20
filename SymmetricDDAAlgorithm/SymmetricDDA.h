#pragma once
#include "pch.h"
#include "Line.h"
#include <vector>

typedef std::vector<std::vector<float>> vectorOfVectorFLoat;

class SYMMETRICDDAALGORITHM_API SymmetricDDA
{
public:
    SymmetricDDA();
    ~SymmetricDDA();

public:
    void symmetricDDALinePixels(Line line, vectorOfVectorFLoat& pixelVertices);
};