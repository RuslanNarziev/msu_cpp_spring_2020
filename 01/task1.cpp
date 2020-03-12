#include "task1.h"

Allocator::Allocator() {
    startptr = nullptr;
    curptr = nullptr;
    alloc_size = 0;
    cursize = 0;
}

Allocator::~Allocator() {
    if(startptr != nullptr) {
        free(startptr);
    }
}

void Allocator::MakeAllocator(size_t maxsize) {
    startptr = (char*) malloc(maxsize);
    if(startptr != NULL)
        cursize = alloc_size = maxsize;
        curptr = startptr;
}

char* Allocator::Alloc(size_t size) {
    if(cursize >= size) {
        cursize -= size;
        curptr += size;
        return curptr - size;
    } else {
        return nullptr;
    }
}

void Allocator::Reset() {
    curptr = startptr;
    cursize = alloc_size;
}

char* Allocator::Get_curptr() {
    return curptr;
}

char* Allocator::Get_startptr() {
    return startptr;
}