#include "task1.h"

int main() {
    MakeAllocator(100);
    char* ptr = Alloc(10);
    Reset();
    char* ptr_2 = Alloc(10);
    if(ptr == ptr_2)
        std::cout << "Reset works correct";
    else
        std::cout << "Reset works incorrect";
    return 0; 
}