#ifndef MODEL_H
#define MODEL_H

#include "map.h"
#include "node.h"
#include "road.h"
#include <QColor>
#include <QGraphicsScene>
#include <QTextBrowser>
#include <QThread>
#include <iostream>
class Model : public QObject {
    Q_OBJECT
public:
    Model();
    void addNode(Node* node);
    void connect_node(Node* n1, Node* n2);
    bool is_connected(Node* n1, Node* n2);
    void setScene(QGraphicsScene* value);
    Node* mapToNode(QGraphicsItem* item)
    {
        return item_to_node[item];
    }

    Road* mapToRoad(QGraphicsItem* item)
    {
        return item_to_road[item];
    }
    void log(QString msg);
    void calculate();
    bool save_to_file();
    bool init_from_file();
    void setNodeColor(Node* node, QColor c = Qt::black);
    void setNodeColor(int id, QColor c = Qt::black);
    void setRoadColor(Node* start, Node* end, QColor c = Qt::black);
    void setRoadColor(int start_id, int end_id, QColor c = Qt::black);
    Road* findRoad(Node* start, Node* end);
    void resetColorForAll();
    void update()
    {
        scene->update();
    }
    void setOutputBox(QTextBrowser* value);
    int getWaitTime();
    void setWaitTime(int value);
    void setTotalDistance(int id, int distance);
    int getWeight(int id)
    {
        return nodes[id]->getWeight();
    }
    void emitAllComplete()
    {
        emit allComplete();
    }
public slots:
    void on_roadChangeColor(int u, int v, QColor c);
    void on_resetColor();
    void on_logMsg(QString msg);
    void on_allComplete();
    void on_setNodeColor(int source, QColor c);
signals:
    void allComplete();

private:
    bool initialized = false;
    int waitTime = 50;
    QVector<Node*> nodes;
    QVector<Road*> roads;
    QVector<int> totalDistance;
    QGraphicsScene* scene;
    QTextBrowser* outputBox;
    QMap<QGraphicsItem*, Node*> item_to_node;
    QMap<QGraphicsItem*, Road*> item_to_road;

    //    void calculate_task();
};

#endif // MODEL_H
