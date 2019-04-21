#ifndef NODE_H
#define NODE_H
#include <QGraphicsEllipseItem>
#include <QPointF>
class Node {
public:
    Node(QPointF);
    const int id;

    QPointF getLocation() const;
    void setLocation(const QPointF& value);

    QGraphicsEllipseItem* getEllipse_item() const;
    void setMovable(bool value)
    {
        ellipse_item->setFlag(QGraphicsItem::ItemIsMovable, value);
    }
    void setColor(QColor c);

    int getWeight() const;
    void setWeight(int value);
    QString to_qstring();

private:
    static int next_id;
    QPointF location;
    int weight = 0;
    QGraphicsEllipseItem* ellipse_item;
};

#endif // NODE_H
