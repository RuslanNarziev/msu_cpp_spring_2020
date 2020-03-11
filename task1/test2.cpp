#include "task1.h"

int main() {
    MakeAllocator(100);
    char* ptr = Alloc(10);
    if(curptr - 10 == ptr) 
        std::cout << "Alloc works correct";
    else
        std::cout << "Alloc works incorrect";
    return 0; 
}