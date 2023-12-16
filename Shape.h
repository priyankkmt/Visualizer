#pragma once
#include "Line.h"

class Shape
{
public:
    Shape();
    Shape(const std::vector<Line>& polyLines);
      

    ~Shape();

    const std::vector<Line>& getShape() const;

    void drawPolygon(QPainter& painter, QVector<QVector2D> polygon, QVector<QVector2D> clipper);

    size_t getSize() const;

    void setShape(std::vector<Line> vl);
private:
    std::vector<Line> mPolyLines;
    std::vector<Point> mPoints;
};