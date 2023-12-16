#include "stdafx.h"
#include "Shape.h"
#include<QPainter>

Shape::Shape()
{

}
Shape::Shape(const std::vector<Line>& polyLines)
    : mPolyLines(polyLines)

{
}

Shape::~Shape()
{
}

const std::vector<Line>& Shape::getShape() const
{
    return mPolyLines;
}
void Shape::drawPolygon(QPainter& painter, QVector<QVector2D> polygon, QVector<QVector2D> clipper) {

    // Draw the original polygon
    QPolygonF poly;
    for (const auto& point : polygon) {
        poly << QPointF(point.x(), point.y());
    }
    painter.setPen(QPen(Qt::blue, 2));
    painter.drawPolygon(poly);
}

size_t Shape::getSize() const
{
    return mPolyLines.size();
}

void Shape::setShape(std::vector<Line> vl)
{
    mPolyLines = vl;
}
