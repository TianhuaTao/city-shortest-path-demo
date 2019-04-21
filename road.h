#ifndef ROAD_H
#define ROAD_H
#include "node.h"
#include <QColor>
#include <QGraphicsLineItem>
class Node;

class Road {
public:
    Road(Node* start, Node* end);

    Node* start_node;
    Node* end_node;

    QGraphicsLineItem* getLine_item() const;
    void setColor(QColor c);
    int getLength();
    QString to_qstring();

private:
    QGraphicsLineItem* line_item;
};

#endif // ROAD_H
