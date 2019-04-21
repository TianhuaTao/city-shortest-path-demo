#ifndef MYGRAPHICSLINEITEM_H
#define MYGRAPHICSLINEITEM_H

#include <QGraphicsItem>
#include <QObject>

class MyGraphicsLineItem : public QGraphicsLineItem {
public:
    MyGraphicsLineItem(QGraphicsItem* start_point, QGraphicsItem* end_point);
    QGraphicsItem* start_point;
    QGraphicsItem* end_point;
};

#endif // MYGRAPHICSLINEITEM_H
