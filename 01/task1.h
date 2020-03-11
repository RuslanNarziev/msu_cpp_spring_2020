#pragma once 
#include <iostream>

extern char* startptr;
extern char* curptr;
extern size_t alloc_size;
extern size_t cursize;
extern void MakeAllocator(size_t maxsize);
extern char* Alloc(size_t size);
extern void Reset();