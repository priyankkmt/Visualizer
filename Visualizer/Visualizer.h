#pragma once

#include <QtWidgets/QMainWindow>
#include <vector>

#include "OpenGLWindow.h"
#include "SymmetricDDA.h"
#include "Grid.h"
#include "HodgmanPolygonClipping.h"
#include "Line.h"
#include "Hermite.h"
#include "Bazier.h"
#include "BSPline.h"

typedef std::vector<Point> pointList;
typedef std::vector<float> floatVector;
typedef std::vector<std::vector<float>> vectorOfVectorFLoat;

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWidget* parent = nullptr);
    ~Visualizer();

public:
    vectorOfVectorFLoat mPixelVertices;
    floatVector         mVertices;
    floatVector         mColors;

private:
    void setupUi();
    void retranslateUi();
private:

    QWidget*  centralWidget;
    QLabel*   mSymmetricLabel;
    QLabel*   mClipPolygonLabel;
    QSpinBox* xCoordinateInput;
    QSpinBox* yCoordinateInput;

    QPushButton* mAddButton;
    QPushButton* mAddPolygonButton;
    QPushButton* mAddRegionButton;
    QPushButton* mDarwLineButton;
    QPushButton* mClipPolygonButton;
    QPushButton* mDrawHermitButton;
    QPushButton* mDrawBazierButton;
    QPushButton* mDrawBSlineButton;
    QPushButton* mColorSelector;

    QOpenGLWidget* openGLWidget;
    QMenuBar*      menuBar;
    QToolBar*      mainToolBar;
    QStatusBar*    statusBar;

    OpenGLWindow* mRenderer;

    SymmetricDDA symmetricDDA;
    Grid         grid;
    Hermite*     hermite;
    Bazier*      bezier;
    BSpline*     bsline;

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
    void drawHermitAlgo();
    void drawBezierAlgo();
    void drawBSlineAlgo();
};
