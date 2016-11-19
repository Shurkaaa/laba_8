#include "triangleitem.h"
#include <QPolygonF>

TriangleItem::TriangleItem()
{
    QPolygonF polygon;
    polygon << QPointF(100, 200) << QPointF(0, 0) << QPointF(0, 150);
    this->setPolygon(polygon);
    setFlags(ItemIsMovable | ItemIsSelectable);
}
