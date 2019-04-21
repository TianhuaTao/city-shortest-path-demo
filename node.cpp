#include "node.h"
#include <QBrush>
#include <QPen>
#include <sstream>
int Node::next_id = 0;

Node::Node(QPointF point)
    : id(next_id++)
    , location(point)
{
    ellipse_item = new QGraphicsEllipseItem(0, 0, 20, 20);
    ellipse_item->setFlags(QGraphicsItem::ItemIsMovable
        | QGraphicsItem::ItemIsSelectable
        | QGraphicsItem::ItemIsFocusable);
    ellipse_item->setZValue(id + 1);
    QPen pen;
    pen.setWidth(4);
    ellipse_item->setBrush(QBrush(Qt::black));

    QPointF point_center(point.x() - 10, point.y() - 10);
    ellipse_item->setPos(point_center);
}

QPointF Node::getLocation() const
{
    return location;
}

void Node::setLocation(const QPointF& value)
{
    location = value;
}

QGraphicsEllipseItem* Node::getEllipse_item() const
{
    return ellipse_item;
}

void Node::setColor(QColor c)
{
    ellipse_item->setBrush(c);
}

int Node::getWeight() const
{
    return weight;
}

void Node::setWeight(int value)
{
    weight = value;
}

QString Node::to_qstring()
{
    std::stringstream ss;
    std::string str;
    ss << id << " " << location.x() << " " << location.y() << " " << weight;
    str = ss.str();
    return QString::fromUtf8(str.c_str());
}
