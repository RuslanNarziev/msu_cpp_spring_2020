#include "task3.h"

int main() {
    Matrix A = Matrix(4, 5);
    std::cout << "number of rows: " << A.Get_rows() << "\n";
    std::cout << "number of columns: " << A.Get_columns() << "\n";
    std::cout << "A[0][6] = 0" << "\n";
    try {
        A[0][6] = 0;
    }
    catch(std::out_of_range) {
        std::cout << "Error caught";
    }
}