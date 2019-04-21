//
// Created by Sam on 2018/12/3.
//

#ifndef SHORTESTPATH_MAP_H
#define SHORTESTPATH_MAP_H

#include "matrix.h"

class Map {
    int edge_count;
    int node_count;
    int* weight;

    Matrix* matrix;

public:
    Map(int node_count);

    ~Map()
    {
        delete matrix;
        delete weight;
    }

    int get_node_count() const { return node_count; }

    int length(int node1, int node2);

    void connect(int node1, int node2, int length);

    void set_weight(int node, int w)
    {
        weight[node] = w;
    }

    int get_weight(int node)
    {
        return weight[node];
    }
};

#endif //SHORTESTPATH_MAP_H
