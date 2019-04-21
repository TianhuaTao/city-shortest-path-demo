//
// Created by Sam on 2018/12/3.
//

#ifndef SHORTESTPATH_DIJKSTRA_H
#define SHORTESTPATH_DIJKSTRA_H

#include "map.h"
#include "model.h"
#include <QThread>
#include <cmath>
#include <limits>
class Dijkstra : public QObject {
    Q_OBJECT
public:
    Dijkstra(Map* map, int source, Model* m);

    ~Dijkstra();

    void calculate();
    const double error = 0.001;
signals:
    void roadChangeColor(int, int, QColor);
    void resetColor();
    void logMsg(QString msg);
    void setNodeColor(int, QColor);

protected:
    void run();

private:
    Model* model;
    Map* map;
    int source;
    int* dist;
    int* pre;

    int NONE = -1;
    const int INF = INT_MAX;
};

#endif //SHORTESTPATH_DIJKSTRA_H
