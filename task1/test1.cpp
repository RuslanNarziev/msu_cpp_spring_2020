#include "task1.h"

int main() {
    MakeAllocator(1000);
    if(curptr != NULL)
        std::cout << "Memory has allocated";
    else
        std::cout << "Memory has not allocated";
    return 0; 
}