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

private:
    
    QWidget* centralWidget;
    QWidget* gridLayoutWidget;
    QGridLayout* gridLayout;

    QSpinBox* spinBox;
    QSpinBox* yCoordinateInput;

    QLabel* symmetricDDALable;
    QLabel* polygonClippingLable;
    
    QOpenGLWidget* openGLWidget;

    QPushButton* addButton;
    QPushButton* drawLineButton;
    QPushButton* clipPolyButton;
    QPushButton* addPolyButton;
    QPushButton* addRegionButton;

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