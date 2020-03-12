#pragma once 
#include <iostream>

class Allocator{
    char* startptr;
    char* curptr;
    size_t alloc_size;
    size_t cursize;
public:
    Allocator();
    ~Allocator();
    char* Get_curptr();
    char* Get_startptr();
    void MakeAllocator(size_t maxsize);
    char* Alloc(size_t size);
    void Reset();
};