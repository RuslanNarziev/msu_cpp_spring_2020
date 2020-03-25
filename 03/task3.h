#pragma once
#include <iostream>

class Matrix {
    int rows; 
    int columns;
    int* data;
public:
    Matrix(int r, int c);
    int Get_rows();
    int Get_columns();
    Matrix & operator*=(int num);
    bool operator==(Matrix & A);
    bool operator!=(Matrix & A);
    void Print_matrix();

    class Row {
        int* row;
        int cols;
    public:
        Row(int* _row, int _col);
        int & operator[](int col);
    };

    Row operator[](int row);
};