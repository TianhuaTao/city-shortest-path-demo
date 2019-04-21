//
// Created by Sam on 2018/12/3.
//

#ifndef SHORTESTPATH_MATRIX_H
#define SHORTESTPATH_MATRIX_H

#include <vector>

class Matrix {
    int row_count;
    int col_count;

public:
    Matrix(int row, int col, int init_val = 0);

    ~Matrix();

    void set_value(int row, int col, int value);

    int get_value(int row, int col);

    int** matrix = nullptr;
    //    std::vector<std::vector<int>> rows;
    //    std::vector<int> cols;

private:
    void printAll();
};

#endif //SHORTESTPATH_MATRIX_H
