#include "stdafx.h"
#include "OpenGLWindow.h"
#include "SymmetricDDA.h"
#include "Grid.h"
#include "HodgmanPolygonCLipping.h"

#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <QDebug>

OpenGLWindow::OpenGLWindow(const QColor& background, QWidget* parent) :
    mBackground(background)
{
    setParent(parent);

    setMinimumSize(1000, 1050);

    const QStringList list = { "vertexShader.glsl" , "fragmentShader.glsl" };
    mShaderWatcher = new QFileSystemWatcher(list, this);

    connect(mShaderWatcher, &QFileSystemWatcher::fileChanged, this, &OpenGLWindow::shaderWatcher);

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
    matrix.rotate(rotationAngle);

    mProgram->setUniformValue("r", r);
    mProgram->setUniformValue("g", g);
    mProgram->setUniformValue("b", b);

    mProgram->setUniformValue(m_matrixUniform, matrix);

    floatVector vertices;
    floatVector colors;

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

void OpenGLWindow::setVectorOfLines(floatVector& vectorOfLines)
{
    verticesOfOrignalLine = vectorOfLines;
}

void OpenGLWindow::setColorOfLines(floatVector& colorOfLines)
{
    colorOfOrignalLine = colorOfLines;
}

void OpenGLWindow::setPolygon(Shape& clippedPolygon)
{
    mClipPolygon = clippedPolygon;
}

void OpenGLWindow::updateData(const floatVector& vertices, const floatVector& colors)
{
    verticesOfOrignalLine = vertices;
    colorOfOrignalLine = colors;
    update();  // Schedule a repaint
}

void OpenGLWindow::drawPolygon(Shape& s, floatVector& vertices, floatVector& colors)
{
    for (int i = 0; i < s.getSize(); i++)
    {
        Line l = s.getShape().at(i);
        vertices.push_back(l.p1().x());
        vertices.push_back(l.p1().y());

        vertices.push_back(l.p2().x());
        vertices.push_back(l.p2().y());


        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
    }
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event) {
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

        rotationAngle = rotX * rotY * rotationAngle;
        update();
    }
    lastPos = event->pos();
}

QString OpenGLWindow::readShader(QString filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "Invalid file";

    QTextStream stream(&file);
    QString line = stream.readLine();

    while (!stream.atEnd()) {
        line.append(stream.readLine());
    }
    file.close();
    return line;
}

void OpenGLWindow::shaderWatcher()
{
    QString vertexShaderSource = readShader("vertexShader.glsl");
    QString fragmentShaderSource = readShader("fragmentShader.glsl");

    mProgram->release();
    mProgram->removeAllShaders();
    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
}

void OpenGLWindow::selectCurveColor()
{
    QColorDialog colorDialog(this);
    QColor selectedColor = colorDialog.getColor();

    if (selectedColor.isValid()) {
        // Set the selected color to the curves or store it for later use
        r = selectedColor.redF();
        g = selectedColor.greenF();
        b = selectedColor.blueF();
        emit shapeUpdate();  // Trigger an update to redraw the curves with the new color
    }
}


void OpenGLWindow::initializeGL()
{
    QString vertexShaderSource = readShader("vertexShader.glsl");
    QString fragmentShaderSource = readShader("fragmentShader.glsl");

    initializeOpenGLFunctions();

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
    m_posAttr = mProgram->attributeLocation("posAttr");
    if (m_posAttr == -1 || m_colAttr == -1 || m_matrixUniform == -1)
    {
        qDebug() << "Shader attribute or uniform location error.";
        // Handle the error appropriately, e.g., return or throw an exception
    }
}
