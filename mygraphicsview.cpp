#include "mygraphicsview.h"
#include <QMouseEvent>
#include <QPoint>
MyGraphicsView::MyGraphicsView(QWidget* parent)
    : QGraphicsView(parent)
{
}

void MyGraphicsView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        //        QPoint  point;
        QPoint point = event->pos(); //QGraphicsView的坐标
        emit MC(point);
    }
    QGraphicsView::mousePressEvent(event);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        //        QPoint  point;
        QPoint point = event->pos(); //QGraphicsView的坐标

        emit MM(point);
    }
    QGraphicsView::mouseMoveEvent(event);
}
