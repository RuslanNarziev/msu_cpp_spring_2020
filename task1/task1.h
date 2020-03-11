#pragma once
#include <iostream>

char* startptr = nullptr;
char* curptr = nullptr;
size_t alloc_size = 0;
size_t cursize = 0;
void MakeAllocator(size_t maxsize);
char* Alloc(size_t size);
void Reset();