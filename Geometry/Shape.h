#pragma once
#include "pch.h"
#include "Line.h"

#include<vector>

typedef std::vector<std::vector<float>> vectorOfVectorFLoat;

class GEOMETRY_API Shape
{
public:
    Shape();
    Shape(const std::vector<Line>& polyLines);


    ~Shape();

    const std::vector<Line>& getShape() const;

    //void drawPolygon(QPainter& painter, vectorOfVectorFLoat polygon, vectorOfVectorFLoat clipper);

    size_t getSize() const;

    void setShape(std::vector<Line> vl);
private:
    std::vector<Line> mPolyLines;
    std::vector<Point> mPoints;
};