#include "task3.h"

int main() {
    Matrix A = Matrix(4, 5);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 5; j++)
            A[i][j] = i + j;
    A.Print_matrix();
    std::cout << "\n" << "A *= 3" << "\n\n";
    A *= 3;
    A.Print_matrix();
}