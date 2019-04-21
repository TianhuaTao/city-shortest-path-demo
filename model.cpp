#include "model.h"
#include "dijkstra.h"
#include "map.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <iostream>
#include <thread>
Model::Model()
{
    QObject::connect(this, &Model::allComplete, this, &Model::on_allComplete);
}

void Model::addNode(Node* node)
{
    initialized = true;
    nodes.push_back(node);
    scene->addItem(node->getEllipse_item());
    scene->update();
    item_to_node.insert(node->getEllipse_item(), node);
}

void Model::connect_node(Node* n1, Node* n2)
{
    initialized = true;
    Road* road = new Road(n1, n2);
    n1->setMovable(false);
    n2->setMovable(false);
    roads.push_back(road);
    scene->addItem(road->getLine_item());
    scene->update();
    item_to_road.insert(road->getLine_item(), road);
}

void Model::setScene(QGraphicsScene* value)
{
    scene = value;
}

void Model::log(QString msg)
{
    outputBox->insertPlainText(msg);
}

void calculate_task(Map* m, Model* model)
{
    int v = m->get_node_count();
    for (int j = 0; j < v; ++j) {
        std::cout << "source " << j << ": ";

        Dijkstra solution(m, j, model);
        solution.calculate();
    }
    model->emitAllComplete();
}

void Model::calculate()
{
    //    calculate_task(nodes, roads, this);
    //    roads[0]->setColor(Qt::red);
    //    std::thread t(calculate_task, nodes, roads, this);
    //    t.detach();
    int v, e;
    v = nodes.count();
    e = roads.count();
    totalDistance.clear();
    totalDistance.resize(v);
    Map* map = new Map(v);
    for (int i = 0; i < e; ++i) {
        Road* r = roads[i];
        int node1 = r->start_node->id;
        int node2 = r->end_node->id;
        int length = roads[i]->getLength();

        map->connect(node1, node2, length);
    }
    log("[Calculating Matrix]\n");
    //    calculate_task(map, this);
    std::thread* t = new std::thread(calculate_task, map, this);
    t->detach();
    //        MyQThread* t = new MyQThread(map, this);
    //        t->start();
}

bool Model::save_to_file()
{
    QFile file("tmp.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream stream(&file);
    stream << nodes.size() << " " << roads.size() << "\n";
    for (int i = 0; i < nodes.size(); i++) {
        qDebug() << nodes[i]->to_qstring();
        stream << nodes[i]->to_qstring() << "\n";
    }
    for (int i = 0; i < roads.size(); i++) {
        qDebug() << roads[i]->to_qstring();
        stream << roads[i]->to_qstring() << "\n";
    }
    file.close();
    return true;
}

bool Model::init_from_file()
{
    if (initialized)
        return false;
    initialized = true;

    QFile file("tmp.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream in(&file);
    int node_cnt;
    int road_cnt;
    in >> node_cnt >> road_cnt;
    for (int i = 0; i < node_cnt; i++) {
        int id;
        double x;
        double y;
        int weight;
        in >> id >> x >> y >> weight;

        QPointF p(x, y);
        Node* node = new Node(p);
        node->setWeight(weight);

        addNode(node);
    }
    for (int i = 0; i < road_cnt; i++) {
        int id1, id2;
        in >> id1 >> id2;
        //        Road* road = new Road(nodes[id1], nodes[id2]);
        connect_node(nodes[id1], nodes[id2]);
    }

    file.close();

    return true;
}

void Model::setNodeColor(Node* node, QColor c)
{
    node->setColor(c);
    scene->update();
}

void Model::setNodeColor(int id, QColor c)
{
    Node* n = nodes[id];
    setNodeColor(n, c);
}

void Model::setRoadColor(Node* start, Node* end, QColor c)
{
    Road* r = findRoad(start, end);
    if (r) {
        r->setColor(c);
    }
}

void Model::setRoadColor(int start_id, int end_id, QColor c)
{
    Node* n1 = nodes[start_id];
    Node* n2 = nodes[end_id];
    setRoadColor(n1, n2, c);
}

// low efficiency
Road* Model::findRoad(Node* start, Node* end)
{
    Road* result = nullptr;
    for (int i = 0; i < roads.count(); i++) {
        Road* r = roads[i];
        if ((r->start_node == start && r->end_node == end) || (r->start_node == end && r->end_node == start)) {
            result = r;
            break;
        }
    }
    return result;
}

void Model::resetColorForAll()
{
    for (int i = 0; i < nodes.count(); i++) {
        nodes[i]->setColor(Qt::black);
    }
    for (int i = 0; i < roads.count(); i++) {
        roads[i]->setColor(Qt::darkGray);
    }
}

void Model::on_roadChangeColor(int u, int v, QColor c)
{
    setRoadColor(u, v, c);
}

void Model::on_resetColor()
{
    resetColorForAll();
}

void Model::on_logMsg(QString msg)
{
    log(msg);
}

void Model::on_allComplete()
{
    int best = INT_MAX;
    int best_id = -1;
    log(QString("[Total distance]\n"));
    for (int i = 0; i < totalDistance.size(); i++) {
        int dis = totalDistance[i];
        if (dis < best) {
            best = dis;
            best_id = i;
        }
        log(QString("source %1: %2\n").arg(i).arg(dis));
    }
    log(QString("Best location: source = %1, distance = %2\n").arg(best_id).arg(best));
    setNodeColor(best_id, Qt::blue);
}

void Model::on_setNodeColor(int source, QColor c)
{
    setNodeColor(source, c);
}

void Model::setWaitTime(int value)
{
    waitTime = value;
}

void Model::setTotalDistance(int id, int distance)
{
    totalDistance[id] = distance;
}

void Model::setOutputBox(QTextBrowser* value)
{
    outputBox = value;
}

int Model::getWaitTime()
{
    return waitTime;
}
