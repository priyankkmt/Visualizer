#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"

Visualizer::Visualizer(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    connect(addButton, &QPushButton::clicked, this, &Visualizer::addPoints);
    connect(drawLineButton, &QPushButton::clicked, this, &Visualizer::drawLine);
    connect(clipPolyButton, &QPushButton::clicked, this, &Visualizer::clipPolygon);
    connect(addPolyButton, &QPushButton::clicked, this, &Visualizer::addPolygon);
    connect(addRegionButton, &QPushButton::clicked, this, &Visualizer::addRegion);
}

Visualizer::~Visualizer()
{}

void Visualizer::addPoints()
{
    double xCoordinate = spinBox->value();
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

void Visualizer::drawLine()
{
    Point pt1 = mLinePoints[0];
    Point pt2 = mLinePoints[1];

    Line line(pt1, pt2);

    mVertices << pt1.x() << pt1.y();
    mVertices << pt2.x() << pt2.y();

    mColors << 0.0f << 1.0f << 0.0f;
    mColors << 0.0f << 1.0f << 0.0f;

    grid.drawGrid(mVertices, mColors);
    symmetricDDA.symmetricDDALinePixels(line, mPixelVertices);

    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    mRenderer->updateData(mVertices, mColors);
}

void Visualizer::setupUi() {
    resize(1020, 1000);
    centralWidget = new QWidget(this);

    centralWidget->setObjectName("centralWidget");
    //setCentralWidget(centralWidget);
    

    gridLayoutWidget = new QWidget(centralWidget);
    gridLayoutWidget->setObjectName("gridLayoutWidget");
    gridLayoutWidget->setGeometry(QRect(10, 0, 821, 411));


    //grid
    gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setSpacing(3);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName("gridLayout");
    //gridLayout->setSizeConstraint(1000);
    gridLayout->setContentsMargins(0, 0, 0, 0);


    spinBox = new QSpinBox(gridLayoutWidget);
    spinBox->setObjectName("spinBox");

    gridLayout->addWidget(spinBox, 2, 0, 1, 1);

    yCoordinateInput = new QSpinBox(gridLayoutWidget);
    yCoordinateInput->setObjectName("yCoordinateInput");

    gridLayout->addWidget(yCoordinateInput, 2, 1, 1, 1);

    symmetricDDALable = new QLabel(gridLayoutWidget);
    symmetricDDALable->setObjectName("symmetricDDALable");
    symmetricDDALable->setText("Symmetric DDA");

    gridLayout->addWidget(symmetricDDALable, 0, 0, 1, 1);


    polygonClippingLable = new QLabel(gridLayoutWidget);
    polygonClippingLable->setObjectName("polygonClippingLable");
    polygonClippingLable->setText("Clip Polygon");

    gridLayout->addWidget(polygonClippingLable, 0, 1, 1, 1);

    openGLWidget = new QOpenGLWidget(gridLayoutWidget);
    openGLWidget->setObjectName("openGLWidget");
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
    openGLWidget->setSizePolicy(sizePolicy);
    openGLWidget->setMinimumSize(200, 200);
    gridLayout->addWidget(openGLWidget, 5, 0, 10, 3);

    addButton = new QPushButton(gridLayoutWidget);
    addButton->setObjectName("addButton");
    addButton->setText("Add");
    gridLayout->addWidget(addButton, 2, 2, 1, 1);

    drawLineButton = new QPushButton(gridLayoutWidget);
    drawLineButton->setObjectName("drawLineButton");
    drawLineButton->setText("Draw Line");
    gridLayout->addWidget(drawLineButton, 4, 0, 1, 1);

    clipPolyButton = new QPushButton(gridLayoutWidget);
    clipPolyButton->setObjectName("clipPolyButton");
    clipPolyButton->setText("Clip Polygon");
    gridLayout->addWidget(clipPolyButton, 4, 1, 1, 1);

    addPolyButton = new QPushButton(gridLayoutWidget);
    addPolyButton->setObjectName("addPolyButton");
    addPolyButton->setText("Add Region");
    gridLayout->addWidget(addPolyButton, 3, 0, 1, 1);

    addRegionButton = new QPushButton(gridLayoutWidget);
    addRegionButton->setObjectName("addRegionButton");
    addRegionButton->setText("Add Polygon");
    gridLayout->addWidget(addRegionButton, 3, 1, 1, 1);

    

    setCentralWidget(centralWidget);

    mRenderer = new OpenGLWindow(QColor(1.0f, 1.0f, 0.0f), openGLWidget);

    menuBar = new QMenuBar(this);
    menuBar->setObjectName("menuBar");
    menuBar->setGeometry(QRect(0, 0, 842, 22));
    setMenuBar(menuBar);
    mainToolBar = new QToolBar(this);
    mainToolBar->setObjectName("mainToolBar");
    addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(this);
    statusBar->setObjectName("statusBar");
    setStatusBar(statusBar);
} 