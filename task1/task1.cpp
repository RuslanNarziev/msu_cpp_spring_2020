#include <iostream>

char* startptr = nullptr;
char* curptr = nullptr;
size_t alloc_size = 0;
size_t cursize = 0;

void MakeAllocator(size_t maxsize) {
    startptr = (char*) malloc(maxsize);
    if(startptr != NULL)
        cursize = alloc_size = maxsize;
}

char* Alloc(size_t size) {
    if(cursize >= size) {
        cursize -= size;
        curptr += size;
        return curptr - size;
    } else {
        return nullptr;
    }
}

void Reset() {
    curptr = startptr;
    cursize = alloc_size;
}