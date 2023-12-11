#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;

class QOpenGLPaintDevice;

class OpenGLWindow :public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWindow(const QColor& background, QMainWindow* parent);
    ~OpenGLWindow();

protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();
    void drawGrid(QVector<GLfloat>& vertices, QVector<GLfloat>& colors);
    void SymmetricDDA(float x1, float y1, float x2, float y2, QVector<GLfloat>& vertices, QVector<GLfloat>& colors);
    void fillPolygon(const QVector<QVector2D>& squareVertices, const QVector3D& fillColor);
    void sutherLandHodgeMan(QVector<QVector2D>& polyVertices, const QVector<QVector2D>& clippedVertices);
    void clipPolygon(QVector<QVector2D>& polyVertices, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
    float xIntersect(float x1, float y1, float x2, float y2,float x3, float y3, float x4, float y4);
    float yIntersect(float x1, float y1, float x2, float y2,float x3, float y3, float x4, float y4);

private:
    bool mAnimating = false;

    QOpenGLContext*     mContext = nullptr;
    QOpenGLPaintDevice* mDevice = nullptr;

    QOpenGLShader*          mVshader = nullptr;
    QOpenGLShader*          mFshader = nullptr;
    QOpenGLShaderProgram*   mProgram = nullptr;

    QList<QVector3D> mVertices;
    QList<QVector3D> mNormals;

    QOpenGLBuffer mVbo;

    int mVertexAttr;
    int mNormalAttr;
    int mMatrixUniform;

    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;

    GLint mPosAttr{0};
    GLint mColAttr{0};
};