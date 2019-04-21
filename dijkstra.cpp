//
// Created by Sam on 2018/12/3.
//

#include "dijkstra.h"
#include <QTimer>
#include <chrono>
#include <ctime>
#include <iostream>
#include <set>
#include <thread>
using std::cout;
using std::set;

void wait(int time = 1)
{
    for (int i = 0; i < time; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

Dijkstra::Dijkstra(Map* map, int source, Model* m)
    : model(m)
    , map(map)
    , source(source)
{
    int node_count = map->get_node_count();
    dist = new int[node_count]();
    pre = new int[node_count]();

    for (int i = 0; i < node_count; ++i) {
        dist[i] = INF;
        pre[i] = NONE;
    }

    dist[source] = 0;

    QObject::connect(this, &Dijkstra::roadChangeColor, m, &Model::on_roadChangeColor);
    QObject::connect(this, &Dijkstra::resetColor, m, &Model::on_resetColor);
    QObject::connect(this, &Dijkstra::logMsg, m, &Model::on_logMsg);
    QObject::connect(this, &Dijkstra::setNodeColor, m, &Model::on_setNodeColor);
}

void Dijkstra::calculate()
{
    emit logMsg(QString("Source %1: ").arg(source));
    emit resetColor();
    model->update();
    wait(model->getWaitTime());

    emit setNodeColor(source, Qt::green);
    //    model->setNodeColor(source, Qt::green);
    model->update();
    wait(model->getWaitTime());

    set<int> Q; //未计算顶点
    for (int i = 0; i < map->get_node_count(); ++i) {
        Q.insert(i);
    }

    while (!Q.empty()) {
        int u = *Q.begin();
        for (auto it = Q.begin(); it != Q.end(); it++) {
            if (dist[*it] < dist[u])
                u = *it;
        }

        Q.erase(u); //取出dist[u]最小的节点u
        if (u != source) {
            //            model->setNodeColor(u, Qt::red);
            emit setNodeColor(u, Qt::red);
            model->update();
            wait(model->getWaitTime());
        }
        int pre_of_u = pre[u];
        if (pre_of_u != -1) {
            emit roadChangeColor(u, pre_of_u, Qt::red);
            model->update();
            wait(model->getWaitTime());
        }

        set<int> neighbour_of_u; //取出u的所有相邻、未访问节点
        for (int i = 0; i < map->get_node_count(); ++i) {
            if (i == u)
                continue;
            if (Q.find(i) == Q.end()) //not in Q
                continue;
            if (map->length(u, i) != -1) {
                neighbour_of_u.insert(i);
                //                model->setNodeColor(i, Qt::yellow);
                emit setNodeColor(i, Qt::yellow);
                model->update();
                wait(model->getWaitTime());
            }
        }

        for (auto it = neighbour_of_u.begin(); it != neighbour_of_u.end(); it++) {
            int v = *it;
            int alt = dist[u] + map->length(u, v);
            //            model->setRoadColor(u, v, Qt::red);
            emit roadChangeColor(u, v, Qt::blue);
            model->update();
            wait(model->getWaitTime());
            emit roadChangeColor(u, v, Qt::darkGray);
            model->update();
            wait(model->getWaitTime());
            if (alt < dist[v]) { //更新距离
                dist[v] = alt;
                pre[v] = u;
            }
        }
    }
    int total_dis = 0;
    for (int j = 0; j < map->get_node_count(); ++j) {
        total_dis += dist[j] * model->getWeight(j);
        cout << dist[j] << " ";
        emit logMsg(QString("%1 ").arg(dist[j]));
    }

    cout << std::endl;

    emit logMsg(QString("\n"));
    model->setTotalDistance(source, total_dis);
}

Dijkstra::~Dijkstra()
{
    delete[] dist;
    delete[] pre;
}
