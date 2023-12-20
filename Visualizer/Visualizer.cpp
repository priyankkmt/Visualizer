#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"

Visualizer::Visualizer(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    connect(AddButton, &QPushButton::clicked, this, &Visualizer::addPoints);
    connect(darwLineButton, &QPushButton::clicked, this, &Visualizer::drawLine);
    connect(clipPolygonButton, &QPushButton::clicked, this, &Visualizer::clipPolygon);
    connect(addPolygonButton, &QPushButton::clicked, this, &Visualizer::addPolygon);
    connect(addRegionButton, &QPushButton::clicked, this, &Visualizer::addRegion);
    connect(drawHermitButton, &QPushButton::clicked, this, &Visualizer::drawHermitAlgo);
    connect(drawBazierButton, &QPushButton::clicked, this, &Visualizer::drawHermitAlgo);
}

Visualizer::~Visualizer()
{}

void Visualizer::addPoints()
{
    double xCoordinate = xCoordinateInput->value();
    double yCoordinate = yCoordinateInput->value();

    Point p = Point(xCoordinate,yCoordinate);
    mLinePoints.push_back(p);
}

void Visualizer::addPolygon()
{
    mPolygonPoints = mLinePoints;
    Line l1(mPolygonPoints[0], mPolygonPoints[1]);
    Line l2(mPolygonPoints[1], mPolygonPoints[2]);
    Line l3(mPolygonPoints[2], mPolygonPoints[3]);
    Line l4(mPolygonPoints[3], mPolygonPoints[0]);

    std::vector<Line> lines{ l1,l2,l3,l4 };
    mPolygon.setShape(lines);
    mLinePoints.clear();
}

void Visualizer::addRegion()
{
    mRegionPoints = mLinePoints;
    Line l1(mRegionPoints[0], mRegionPoints[1]);
    Line l2(mRegionPoints[1], mRegionPoints[2]);
    Line l3(mRegionPoints[2], mRegionPoints[3]);
    Line l4(mRegionPoints[3], mRegionPoints[0]);

    std::vector<Line> lines{ l1,l2,l3,l4 };
    mRegion.setShape(lines);
    mLinePoints.clear();
}

void Visualizer::clipPolygon()
{
    HodgmanPolygonClipping hodgmanPolygonClipping(mRegion, mPolygon);
    Shape sh = hodgmanPolygonClipping.getClippedPolygon();
    mRenderer->setPolygon(sh);
}

//BSline algo
void Visualizer::drawBSlineAlgo()
{
    bsline = new BSpline();
    bsline->evaluate(mLinePoints,mVertices,mColors,1);

    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    mRenderer->updateData(mVertices, mColors);
}


//Bezier Algo
void Visualizer::drawBezierAlgo()
{
    bezier = new Bazier(mLinePoints);
    bezier->calculateBazier( mVertices, mColors);

    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    mRenderer->updateData(mVertices, mColors);
}


//Hermit Algo
void Visualizer::drawHermitAlgo()
{
    hermite = new Hermite(mLinePoints);
    hermite->calculateHermite(mVertices, mColors);

    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    mRenderer->updateData(mVertices, mColors);
}

// SymmetricDDA
void Visualizer::drawLine()
{
    Point pt1 = mLinePoints[0];
    Point pt2 = mLinePoints[1];

    Line line(pt1, pt2);

    mVertices.push_back(pt1.x());
    mVertices.push_back(pt1.y());

    mVertices.push_back(pt2.x());
    mVertices.push_back(pt2.y());

    mColors.push_back(0.0f);
    mColors.push_back(1.0f);
    mColors.push_back(0.0f);

    mColors.push_back(0.0f);
    mColors.push_back(1.0f); 
    mColors.push_back(0.0f);

    grid.drawGrid(mVertices, mColors);
    symmetricDDA.symmetricDDALinePixels(line, mPixelVertices);

    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    mRenderer->updateData(mVertices, mColors);
}

void Visualizer::setupUi()
{
    resize(1472, 802);
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");

    symmetricLabel = new QLabel(centralWidget);
    symmetricLabel->setObjectName("symmetricLabel");
    symmetricLabel->setGeometry(QRect(40, 0, 91, 16));

    clipPolygonLabel = new QLabel(centralWidget);
    clipPolygonLabel->setObjectName("clipPolygonLabel");
    clipPolygonLabel->setGeometry(QRect(160, 0, 81, 16));

    xCoordinateInput = new QSpinBox(centralWidget);
    xCoordinateInput->setObjectName("xCoordinateInput");
    xCoordinateInput->setGeometry(QRect(40, 20, 71, 22));

    yCoordinateInput = new QSpinBox(centralWidget);
    yCoordinateInput->setObjectName("yCoordinateInput");
    yCoordinateInput->setGeometry(QRect(150, 20, 81, 22));

    AddButton = new QPushButton(centralWidget);
    AddButton->setObjectName("AddButton");
    AddButton->setGeometry(QRect(260, 20, 75, 24));

    addPolygonButton = new QPushButton(centralWidget);
    addPolygonButton->setObjectName("addPolygonButton");
    addPolygonButton->setGeometry(QRect(40, 50, 75, 24));

    addRegionButton = new QPushButton(centralWidget);
    addRegionButton->setObjectName("addRegionButton");
    addRegionButton->setGeometry(QRect(150, 50, 75, 24));

    drawHermitButton = new QPushButton(centralWidget);
    drawHermitButton->setObjectName("drawHermit");
    drawHermitButton->setGeometry(QRect(260, 50, 75, 24));

    darwLineButton = new QPushButton(centralWidget);
    darwLineButton->setObjectName("darwLineButton");
    darwLineButton->setGeometry(QRect(40, 80, 75, 24));

    clipPolygonButton = new QPushButton(centralWidget);
    clipPolygonButton->setObjectName("clipPolygonButton");
    clipPolygonButton->setGeometry(QRect(150, 80, 75, 24));

    drawBazierButton = new QPushButton(centralWidget);
    drawBazierButton->setObjectName("drawBezier");
    drawBazierButton->setGeometry(QRect(260, 80, 75, 24));

    drawBSlineButton = new QPushButton(centralWidget);
    drawBSlineButton->setObjectName("drawBezier");
    drawBSlineButton->setGeometry(QRect(370, 80, 75, 24));

    openGLWidget = new QOpenGLWidget(centralWidget);
    openGLWidget->setObjectName("openGLWidget");
    openGLWidget->setGeometry(QRect(40, 110, 521, 331));
    openGLWidget->setMinimumSize(1000, 800);

    setCentralWidget(centralWidget);

    mRenderer = new OpenGLWindow(QColor(1.0f, 1.0f, 0.0f), openGLWidget);

    menuBar = new QMenuBar(this);
    menuBar->setObjectName("menuBar");
    menuBar->setGeometry(QRect(0, 0, 772, 22));

    setMenuBar(menuBar);
    mainToolBar = new QToolBar(this);
    mainToolBar->setObjectName("mainToolBar");

    addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(this);
    statusBar->setObjectName("statusBar");

    setStatusBar(statusBar);

    retranslateUi();
}

void Visualizer::retranslateUi()
{
    setWindowTitle(QCoreApplication::translate("VisualizerClass", "Visualizer", nullptr));
    symmetricLabel->setText(QCoreApplication::translate("VisualizerClass", "Symmetric DDA", nullptr));
    clipPolygonLabel->setText(QCoreApplication::translate("VisualizerClass", "Clip Polygon", nullptr));
    AddButton->setText(QCoreApplication::translate("VisualizerClass", "Add", nullptr));
    addPolygonButton->setText(QCoreApplication::translate("VisualizerClass", "Add Polygon", nullptr));
    addRegionButton->setText(QCoreApplication::translate("VisualizerClass", "Add Region", nullptr));
    darwLineButton->setText(QCoreApplication::translate("VisualizerClass", "Draw Line", nullptr));
    clipPolygonButton->setText(QCoreApplication::translate("VisualizerClass", "Clip Polygon", nullptr));
    drawHermitButton->setText(QCoreApplication::translate("VisualizerClass", "Hermit Algo", nullptr));
    drawBazierButton->setText(QCoreApplication::translate("VisualizerClass", "Bezier Algo", nullptr));
    drawBSlineButton->setText(QCoreApplication::translate("VisualizerClass", "BSline Algo", nullptr));
}
