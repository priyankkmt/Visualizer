#include "stdafx.h"
#include "OpenGLWindow.h"

#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <iostream>

OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) :
    mBackground(background)
{
    setParent(parent);
    setMinimumSize(300, 250);
}
OpenGLWindow::~OpenGLWindow()
{
    reset();
}

void OpenGLWindow::reset()
{
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT);

    mProgram->bind();

    QMatrix4x4 matrix;
    matrix.ortho(-12.0f, 12.0f, -12.0f, 12.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);

    mProgram->setUniformValue(mMatrixUniform, matrix);

    QVector<GLfloat> vertices;
    QVector<GLfloat> colors;

    //drawGrid(vertices,colors);

    //SymmetricDDA(-2.0, -2.5, 5.0, 4.0, vertices, colors);

    QVector<QVector2D> polyVertices;
    polyVertices.append(QVector2D(0, 0));
    polyVertices.append(QVector2D(1, 3));
    polyVertices.append(QVector2D(3, 2));

    QVector3D fillOldPolyColor(0.0f, 1.0f, 1.0f);

    fillPolygon(polyVertices, fillOldPolyColor);

    QVector<QVector2D> clippedVertices;
    clippedVertices.append(QVector2D(0, 0));
    clippedVertices.append(QVector2D(1, 3));
    clippedVertices.append(QVector2D(3, 3));
    clippedVertices.append(QVector2D(3, 2));

    QVector3D fillNewPolyColor(1.0f, 0.0f, 1.0f);

    sutherLandHodgeMan(polyVertices, clippedVertices);

    fillPolygon(polyVertices, fillNewPolyColor);

    GLfloat* verticesData = vertices.data();
    GLfloat* colorsData = colors.data();

    glVertexAttribPointer(mPosAttr, 2, GL_FLOAT, GL_FALSE, 0, verticesData);
    glVertexAttribPointer(mColAttr, 3, GL_FLOAT, GL_FALSE, 0, colorsData);

    glEnableVertexAttribArray(mPosAttr);
    glEnableVertexAttribArray(mColAttr);

    glDrawArrays(GL_LINES, 0, vertices.size()/2);

    glDisableVertexAttribArray(mColAttr);
    glDisableVertexAttribArray(mPosAttr);
}

void OpenGLWindow::sutherLandHodgeMan(QVector<QVector2D>& polyVertices, const QVector<QVector2D>& clippedVertices)
{
    int clippSize = clippedVertices.size();

    for (int i = 0; i < clippSize; i++)
    {
        int k = (i + 1) % clippSize;
        clipPolygon(polyVertices, clippedVertices[i].x(), clippedVertices[i].y(), clippedVertices[k].x(), clippedVertices[k].y());
    }
}

void OpenGLWindow::clipPolygon(QVector<QVector2D>& polyVertices, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    int newSize = 0;
    QVector<QVector2D> newPolyVertices;

    for (int i = 0; i < polyVertices.size(); i++)
    {
        int k = (i + 1) % polyVertices.size();
        int ix = polyVertices[i].x(), iy = polyVertices[i].y();
        int kx = polyVertices[k].x(), ky = polyVertices[k].y();

        int iPos = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);
        int kPos = (x2 - x1) * (ky - y1) - (y2 - y1) * (kx - x1);

        if (iPos < 0 && kPos < 0)
        {
            newPolyVertices.append(QVector2D(kx, ky));
            newSize++;
        }
        else if (iPos >= 0 && kPos < 0)
        {
            float x = xIntersect(x1, y1, x2, y2, ix, iy, kx, ky);
            float y = yIntersect(x1, y1, x2, y2, ix, iy, kx, ky);
            newPolyVertices.append(QVector2D(x, y));
            newSize++;
        }
        else if (iPos < 0 && kPos >= 0)
        {
            float x = xIntersect(x1, y1, x2, y2, ix, iy, kx, ky);
            float y = yIntersect(x1, y1, x2, y2, ix, iy, kx, ky);
            newPolyVertices.append(QVector2D(x, y));
            newSize++;

            newPolyVertices.append(QVector2D(kx, ky));
            newSize++;
        }
    }

    polyVertices = newPolyVertices;
}

float OpenGLWindow::xIntersect(float x1, float y1, float x2, float y2,
    float x3, float y3, float x4, float y4)
{
    float num = (x1 * y2 - y1 * x2) * (x3 - x4) -
        (x1 - x2) * (x3 * y4 - y3 * x4);
    float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    return num / den;
}

float OpenGLWindow::yIntersect(float x1, float y1, float x2, float y2,
    float x3, float y3, float x4, float y4)
{
    float num = (x1 * y2 - y1 * x2) * (y3 - y4) -
        (y1 - y2) * (x3 * y4 - y3 * x4);
    float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    return num / den;
}

void OpenGLWindow::SymmetricDDA(float x1, float y1, float x2, float y2, QVector<GLfloat> &vertices, QVector<GLfloat> &colors)
{
    vertices << x1 << y1;
    vertices << x2 << y2;

    colors << 1.0f << 0.0f << 1.0f;
    colors << 1.0f << 0.0f << 1.0f;

    QVector<QVector2D> pixelVertices;

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

    int i{};
    while (i < pixelVertices.size()) {
        QVector<QVector2D> qv;
        qv.append(pixelVertices[i]);
        i++;
        qv.append(pixelVertices[i]);
        i++;
        qv.append(pixelVertices[i]);
        i++;
        qv.append(pixelVertices[i]);
        i++;

        QVector3D fillColor(1.0f, 1.0f, 0.0f);

        fillPolygon(qv, fillColor);
    }
}

void OpenGLWindow::fillPolygon(const QVector<QVector2D>& squareVertices, const QVector3D& fillColor)
{

    QVector<GLfloat> vertices;
    QVector<GLfloat> colors;

    for (const auto& vertex : squareVertices)
    {
        vertices << vertex.x();
        vertices << vertex.y();
        colors << fillColor.x() << fillColor.y() << fillColor.z();
    }

    GLfloat* verticesData = vertices.data();
    GLfloat* colorsData = colors.data();

    glVertexAttribPointer(mPosAttr, 2, GL_FLOAT, GL_FALSE, 0, verticesData);
    glVertexAttribPointer(mColAttr, 3, GL_FLOAT, GL_FALSE, 0, colorsData);

    glEnableVertexAttribArray(mPosAttr);
    glEnableVertexAttribArray(mColAttr);

    glDrawArrays(GL_POLYGON, 0, vertices.size() / 2);

    glDisableVertexAttribArray(mColAttr);
    glDisableVertexAttribArray(mPosAttr);
}

void OpenGLWindow::drawGrid(QVector<GLfloat> &vertices, QVector<GLfloat> &colors)
{
    float gridSize = 16.0f;

    for (float y = -gridSize / 2; y <= gridSize / 2; y++)
    {
        vertices << -gridSize / 2 << y;
        vertices << gridSize / 2 << y;

        colors << 1.0f << 1.0f << 1.0f;
        colors << 1.0f << 1.0f << 1.0f;
    }
    for (float x = -gridSize / 2; x <= gridSize / 2; x++)
    {
        vertices << x << -gridSize / 2;
        vertices << x << gridSize / 2;

        colors << 1.0f << 1.0f << 1.0f;
        colors << 1.0f << 1.0f << 1.0f;
    }
}

void OpenGLWindow::initializeGL()
{
    static const char* vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

    static const char* fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";

    initializeOpenGLFunctions();

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
    mPosAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(mPosAttr != -1);
    mColAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(mColAttr != -1);
    mMatrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(mMatrixUniform != -1);
}