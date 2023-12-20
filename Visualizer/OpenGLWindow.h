#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <vector>

#include "Grid.h"
#include "SymmetricDDA.h"
#include "HodgmanPolygonClipping.h"
#include "Shape.h"

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;

class QOpenGLPaintDevice;

typedef std::vector<float> floatVector;
typedef std::vector<std::vector<float>> vectorOfVectorFLoat;

class OpenGLWindow :public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWindow(const QColor& background, QWidget* parent);
    ~OpenGLWindow();
    
    void setVectorOfLines(floatVector& vectorOfLines);
    void setColorOfLines(floatVector& colorOfLines);
    void setPolygon(Shape& clippedPolygon);
    void updateData(const floatVector& vertices, const floatVector& colors);
    
protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();
    //void setRegion(double xMin, double yMin, double xMax, double yMax);
    

    void drawPolygon(Shape& s, floatVector& vertices, floatVector& colors);

private:
    bool mAnimating = false;
    QOpenGLContext* mContext = nullptr;
    QOpenGLPaintDevice* mDevice = nullptr;

    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;

    //QList<QVector3D> mVertices;
    //QList<QVector3D> mNormals;
    QOpenGLBuffer mVbo;
    int mVertexAttr;
    int mNormalAttr;
    int mMatrixUniform;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;

    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;
    QVector<QVector2D> pixelVertices;

    Grid grid;
    //QVector<QVector2D> squareVertices;

    floatVector verticesOfOrignalLine;
    floatVector colorOfOrignalLine;

    Shape mClipPolygon;
};