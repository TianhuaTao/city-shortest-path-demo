//
// Created by Sam on 2018/12/3.
//

#include "matrix.h"
#include <iostream>
Matrix::Matrix(int row, int col, int init_val)
{
    row_count = row;
    col_count = col;
    matrix = new int*[row];
    for (int i = 0; i < row; ++i) {
        matrix[i] = new int[col];
        for (int j = 0; j < col; ++j) {
            matrix[i][j] = init_val;
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < row_count; ++i) {
        delete[] matrix[i];
    }
    delete matrix;
}

void Matrix::set_value(int row, int col, int value)
{
    //    std::cout << "set" << std::endl;
    //    printAll();
    matrix[row][col] = value;
    //    printAll();
}

int Matrix::get_value(int row, int col)
{
    //    std::cout << "matrix[row][col] = " << matrix[row][col] << std::endl;
    //    std::cout << "get" << std::endl;
    //    printAll();
    return matrix[row][col];
}

void Matrix::printAll()
{
    //    for (int j = 0; j < row_count; ++j) {
    //        for (int i = 0; i < col_count; ++i) {
    //            std::cout << matrix[j][i] << " ";
    //        }
    //        std::cout << std::endl;
    //    }
}
