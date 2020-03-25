#include "task3.h"

int main() {
    Matrix A = Matrix(4, 5);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 5; j++)
                A[i][j] = 0;
    Matrix B = Matrix(4, 5);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 5; j++)
                B[i][j] = 1;
    Matrix C = Matrix(4, 5);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 5; j++)
                C[i][j] = 0;
    Matrix D = Matrix(4, 6);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 6; j++)
                D[i][j] = 0;
    std::cout << "A\n";
    A.Print_matrix();
    std::cout << "\nB\n";
    B.Print_matrix();
    std::cout << "\nC\n";
    C.Print_matrix();
    std::cout << "\nD\n";
    D.Print_matrix();
    std::cout << "A != B?: " << (A != B) << "\n";
    std::cout << "A == C?: " << (A == C) << "\n";
    std::cout << "A == D?\n";
    try {
        A == D;
    }
    catch(std::out_of_range) {
        std::cout << "Error caught";
    }
}