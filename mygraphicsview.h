#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QMainWindow>
#include <QMouseEvent>
#include <QObject>

class MyGraphicsView : public QGraphicsView {

    Q_OBJECT

public:
    MyGraphicsView(QWidget* parent = 0);

signals:
    void MC(QPoint point); //鼠标单击
    void MM(QPoint point);

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // MYGRAPHICSVIEW_H
