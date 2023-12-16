#include "stdafx.h"
#include "OpenGLWindow.h"
#include "SymmetricDDA.h"
#include "Grid.h"
#include "HodgmanPolygonCLipping.h"

#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>-
#include <QPainter>
#include <QDebug>

OpenGLWindow::OpenGLWindow(const QColor& background, QWidget* parent) :
    mBackground(background)
{
    setParent(parent);

    setMinimumSize(1000, 1050);
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
    matrix.ortho(-32.0f, 32.0f, -32.0f, 32.0f, 0.1f, 100.0f); 
    matrix.translate(0, 0, -2);
    mProgram->setUniformValue(m_matrixUniform, matrix);

    QVector<GLfloat> vertices;
    QVector<GLfloat> colors;


    drawPolygon(mClipPolygon, verticesOfOrignalLine, colorOfOrignalLine);

    GLfloat* verticesData = verticesOfOrignalLine.data();
    GLfloat* colorsData = colorOfOrignalLine.data();

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, verticesData);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colorsData);
    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);
    glDrawArrays(GL_LINES, 0, verticesOfOrignalLine.size() / 2);
    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);
    update();
}

void OpenGLWindow::setVectorOfLines(QVector<GLfloat>& vectorOfLines)
{
    verticesOfOrignalLine = vectorOfLines;
}

void OpenGLWindow::setColorOfLines(QVector<GLfloat>& colorOfLines)
{
    colorOfOrignalLine = colorOfLines;
}

void OpenGLWindow::setPolygon(Shape& clippedPolygon)
{
    mClipPolygon = clippedPolygon;
}

void OpenGLWindow::updateData(const QVector<GLfloat>& vertices, const QVector<GLfloat>& colors)
{
    verticesOfOrignalLine = vertices;
    colorOfOrignalLine = colors;
    update();  // Schedule a repaint
}

void OpenGLWindow::drawPolygon(Shape& s, QVector<GLfloat>& vertices, QVector<GLfloat>& colors)
{
    for (int i = 0; i < s.getSize(); i++)
    {
        Line l = s.getShape().at(i);
        vertices << l.p1().x() << l.p1().y();
        vertices << l.p2().x() << l.p2().y();

        colors << 1.0f << 1.0f << 0.0f;
        colors << 1.0f << 1.0f << 0.0f;
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
    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
}