//
// Created by Sam on 2018/12/3.
//

#include "map.h"
#include <cmath>
Map::Map(int node_count)
    : node_count(node_count)
    , edge_count(0)
{
    matrix = new Matrix(node_count, node_count, -1);
    weight = new int[node_count]();
}

int Map::length(int node1, int node2)
{
    return matrix->get_value(node1, node2);
}

void Map::connect(int node1, int node2, int length)
{
    edge_count++;
    matrix->set_value(node1, node2, length);
    matrix->set_value(node2, node1, length);
}
