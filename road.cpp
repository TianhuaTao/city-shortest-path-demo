#include "road.h"
#include <QDebug>
#include <QPen>
#include <cmath>
#include <sstream>
Road::Road(Node* start, Node* end)
    : start_node(start)
    , end_node(end)
{
    //    MyGraphicsLineItem* line_item = new MyGraphicsLineItem(item1, item2);
    //    //    id_to_lines.insert(item1->data(ID).toInt(),line_item);
    //    line_item->setFlags(QGraphicsItem::ItemIsMovable
    //        | QGraphicsItem::ItemIsSelectable
    //        | QGraphicsItem::ItemIsFocusable);

    //

    //    line_item->setZValue(++frontZ);
    //    scene->addItem(line_item);
    auto x1 = start->getEllipse_item()->pos().x() + 10;
    auto y1 = start->getEllipse_item()->pos().y() + 10;
    auto x2 = end->getEllipse_item()->pos().x() + 10;
    auto y2 = end->getEllipse_item()->pos().y() + 10;
    line_item = new QGraphicsLineItem(x1, y1, x2, y2);
    line_item->setFlag(QGraphicsItem::ItemIsSelectable, false);
    QPen pen(Qt::darkGray);
    pen.setWidth(4);
    line_item->setPen(pen);
    line_item->setZValue(0);
    //    auto y1 = start->pos().y() + 10;
    //    auto x2 = end_point->pos().x() + 10;
    //    auto y2 = end_point->pos().y() + 10;
    //    setLine(x1, y1, x2, y2);
    //    line_item= new QGraphicsLineItem()
}

QGraphicsLineItem* Road::getLine_item() const
{
    return line_item;
}

void Road::setColor(QColor c)
{
    QPen pen(line_item->pen());
    pen.setColor(c);
    line_item->setPen(pen);
}

int Road::getLength()
{
    auto x1 = start_node->getEllipse_item()->pos().x() + 10;
    auto y1 = start_node->getEllipse_item()->pos().y() + 10;
    auto x2 = end_node->getEllipse_item()->pos().x() + 10;
    auto y2 = end_node->getEllipse_item()->pos().y() + 10;

    int length = static_cast<int>(std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
    return length;
}

QString Road::to_qstring()
{
    std::stringstream ss;
    std::string str;
    ss << start_node->id << " " << end_node->id;
    str = ss.str();
    return QString::fromUtf8(str.c_str());
}
