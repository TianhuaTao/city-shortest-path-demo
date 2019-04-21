#include "mygraphicslineitem.h"

MyGraphicsLineItem::MyGraphicsLineItem(QGraphicsItem* start_point, QGraphicsItem* end_point)
    : start_point(start_point)
    , end_point(end_point)
{
    auto x1 = start_point->pos().x() + 10;
    auto y1 = start_point->pos().y() + 10;
    auto x2 = end_point->pos().x() + 10;
    auto y2 = end_point->pos().y() + 10;
    setLine(x1, y1, x2, y2);
}
