#include <iostream>

void* startptr;
void* curptr;
size_t alloc_size;
size_t cursize;
void MakeAllocator(size_t maxsize);
char* Alloc(size_t size);
void Reset();