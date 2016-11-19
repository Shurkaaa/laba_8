#ifndef PAINTERWINDOW_H
#define PAINTERWINDOW_H

#include <QMainWindow>
#include "qgraphicsview.h"
#include <QMenu>
#include "triangleitem.h"
#include <QPair>
#include <QColor>

namespace Ui {
class PainterWindow;
}

class PainterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PainterWindow(QWidget *parent = 0);
    ~PainterWindow();
    void setupMenus();
    void setupSceneThings();
    QIcon createIcon(QColor color);

private:
    Ui::PainterWindow *ui;
    QGraphicsView *mView;
    QGraphicsScene *mScene;

public slots:
    void paintTriangle();
    void rotateItem();
    void  zoomIn();
    void zoomOut();
    void setColor(QAction*);
    void sceneChanged();

};

#endif // PAINTERWINDOW_H
