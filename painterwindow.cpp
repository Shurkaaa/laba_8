#include "painterwindow.h"
#include "ui_painterwindow.h"
#include <QPixmap>
#include <QBrush>
#include<QColor>

PainterWindow::PainterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PainterWindow)
{
    ui->setupUi(this);
    setupSceneThings();
    setupMenus();
}

void PainterWindow::setupMenus() {
    QAction *clearAction = new QAction("Clear window", this);
    connect(clearAction, SIGNAL(triggered()), mScene, SLOT(clear()));

    QAction *rotateAction = new QAction("Rotate", this);
    connect(rotateAction, SIGNAL(triggered()), this, SLOT(rotateItem()));

    QMenu *menu = new QMenu("Paint", this);
    menu->addAction(clearAction);


    QMenu *menu1 = new QMenu("Object", this);
    menu1->addAction(rotateAction);

    QMenuBar* mBar = menuBar();



    QToolBar* tBar= new QToolBar(this);
    tBar->addAction(rotateAction);


    QAction *drawTriangle= new QAction("Triangle",this);
    connect(drawTriangle,SIGNAL(triggered()), this, SLOT(paintTriangle()));
    menu->addAction(drawTriangle);

    QAction *zoomin = new QAction("zoomIn", this);
    connect(zoomin, SIGNAL(triggered()), this, SLOT(zoomIn()));
    tBar->addAction(zoomin);

    QAction *zoomout= new QAction("zoomOut", this);
    connect(zoomout, SIGNAL(triggered()), this, SLOT(zoomOut()));
    tBar->addAction(zoomout);

    auto colors = std::vector<QColor>();
    colors.push_back(QColor(0,255,0));
    colors.push_back(QColor(0,0,255));

    QActionGroup* ag = new QActionGroup(this);

    QToolBar* colorToolbar = new QToolBar(this);
    for(const auto& color: colors) {
        QAction* colorAction = new QAction(createIcon(color), "someColor", this);
        colorAction->setData(color);
        ag->addAction(colorAction);
        colorToolbar->addAction(colorAction);
    }

    connect(ag, SIGNAL(triggered(QAction*)), this, SLOT(setColor(QAction*)) );


    addToolBar(colorToolbar);
    addToolBar(tBar);
    mBar->addMenu(menu);
    mBar->addMenu(menu1);



}

void PainterWindow::sceneChanged() {
    auto items=mScene->selectedItems();
    if (items.count()==0)
    {
       return;
    }
    auto item = items.front();
    auto collidingIts = item->collidingItems();
    for (auto colIt: collidingIts) {
        static_cast<TriangleItem*>(colIt)->setBrush(QBrush(QColor(255, 0, 0)));

    }
}

void PainterWindow::setupSceneThings() {
    mScene = new QGraphicsScene(this);
    mScene->setSceneRect(0, 0, 1000, 1000);
    mView = new QGraphicsView(this);
    mView->setScene(mScene);
    this->setCentralWidget(mView);

    connect(mScene, SIGNAL(changed(const QList<QRectF> &)), this, SLOT(sceneChanged()) );
}

void PainterWindow::paintTriangle() {
    TriangleItem* mTriangle = new TriangleItem();
    mScene->addItem(mTriangle);
    mTriangle->setPos(mView->mapToScene(0,0));
}

void PainterWindow::rotateItem(){
    auto items=mScene->selectedItems();
    if (items.count()==0)
    {
       return;
    }
    auto item = items.front();
    item->setRotation(item->rotation() + 25);
}

void PainterWindow::zoomIn(){

    mView->scale(1.25,1.25);
}

void PainterWindow::zoomOut(){
    mView->scale(0.8,0.8);
}

QIcon PainterWindow::createIcon(QColor color){

    QPixmap mPix(20 , 20);

    QPainter mPaint(&mPix);
    mPaint.setBrush(QBrush(color));
    mPaint.drawRect(0,0,20,20);

    return QIcon(mPix);

}

void PainterWindow::setColor(QAction* mAct){

    auto color = mAct->data().value<QColor>();
    auto items=mScene->selectedItems();
    if (items.count()==0)
    {
       return;
    }
    auto item = items.front();

    static_cast<TriangleItem*>(item)->setBrush(QBrush(color));
}

PainterWindow::~PainterWindow()
{
    delete ui;
}
