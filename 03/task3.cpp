#include "task3.h"

Matrix::Matrix(size_t r, size_t c) {
    data = new int[r * c];
    rows = r;
    columns = c;
}

int Matrix::Get_rows() {
    return rows;
}

int Matrix::Get_columns() {
    return columns;
}

Matrix & Matrix::operator*=(int num) {
    for(int i = 0; i < rows * columns; i++) 
        data[i] = data[i] * num;
    return *this;
}

bool Matrix::operator==(const Matrix & A) const {
    if(A.rows != rows || A.columns != columns)
        throw std::out_of_range("");
    for(int i = 0; i < rows * columns; i++)
        if(data[i] != A.data[i])
            return false;
    return true;
}

bool Matrix::operator!=(const Matrix & A) const {
    return !(*this == A);
}

Matrix::Row Matrix::operator[](int row) {
    if(row < 0 || row >= rows)
        throw std::out_of_range("");
    int* _row = data + row * columns;
    return Row(_row, columns);
} 

int & Matrix::Row::operator[](int col) {
    if(col < 0 || col >= cols)
        throw std::out_of_range("");
    return row[col];
}

Matrix::Row::Row(int* _row, int _col) {
    row = _row;
    cols = _col;
}

void Matrix::Print_matrix() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            std::cout << data[i * columns + j] << " ";
        std::cout << "\n";
    }
}