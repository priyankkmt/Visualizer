#pragma once

#include <QtWidgets/QMainWindow>
#include <vector>

#include "OpenGLWindow.h"
#include "SymmetricDDA.h"
#include "Grid.h"
#include "HodgmanPolygonClipping.h"
#include "Line.h"

typedef std::vector<Point> pointList;

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWidget *parent = nullptr);
    ~Visualizer();

public:
    QVector<QVector2D> mPixelVertices;
    QVector<GLfloat>   mVertices;
    QVector<GLfloat>   mColors;

private:
    void setupUi();
    void retranslateUi();
private:
    
    QWidget* centralWidget;
    QLabel* symmetricLabel;
    QLabel* clipPolygonLabel;
    QSpinBox* xCoordinateInput;
    QSpinBox* yCoordinateInput;

    QPushButton* AddButton;
    QPushButton* addPolygonButton;
    QPushButton* addRegionButton;
    QPushButton* darwLineButton;
    QPushButton* clipPolygonButton;

    QOpenGLWidget* openGLWidget;
    QMenuBar* menuBar;
    QToolBar* mainToolBar;
    QStatusBar* statusBar;

    OpenGLWindow* mRenderer;

    SymmetricDDA symmetricDDA;
    Grid grid;

    Shape mPolygon;
    Shape mRegion;

    pointList mLinePoints;
    pointList mPolygonPoints;
    pointList mRegionPoints;

public slots:
    void drawLine();
    void clipPolygon();
    void addPoints();
    void addPolygon();
    void addRegion();
};