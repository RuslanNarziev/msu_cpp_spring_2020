#include "task1.h"

int main() {
    Allocator al;
    al.MakeAllocator(100);
    char* ptr = al.Alloc(10);
    al.Reset();
    char* ptr_2 = al.Alloc(10);
    if(ptr == ptr_2)
        std::cout << "Reset works correct";
    else
        std::cout << "Reset works incorrect";
    return 0; 
}