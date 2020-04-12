#include <iostream>
#include "task5.h"

int main()  {
    BigInt A = BigInt(10);
    const char* str = "0100";
    BigInt B = BigInt(str);
    std::cout << A << std::endl;
    std::cout << B << std::endl;
}