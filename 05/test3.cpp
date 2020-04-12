#include <iostream>
#include "task5.h"

int main() {
    BigInt A = BigInt(10);
    BigInt B = BigInt(9);
    std::cout << (A > B) << (A == B);
}