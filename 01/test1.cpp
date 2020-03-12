#include "task1.h"

int main() {
    Allocator al;
    al.MakeAllocator(1000);
    if(al.Get_startptr() != NULL)
        std::cout << "Memory has allocated";
    else
        std::cout << "Memory has not allocated";
    return 0; 
}