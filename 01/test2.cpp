#include "task1.h"

int main() {
    Allocator al;
    al.MakeAllocator(100);
    char* ptr = al.Alloc(10);
    if(al.Get_curptr() - 10 == ptr) 
        std::cout << "Alloc works correct";
    else
        std::cout << "Alloc works incorrect";
    return 0; 
}