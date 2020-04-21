#include "task5.h"
#include <cstdlib>

BigInt::BigInt(long long num) {
    //if num = 0 then size = 0
    size = 0;
    sign = true;
    if (num < 0) {
        num = -num;
        sign = false;
    }
    while(num) {
        if(size) {
            number = (char*) realloc(number, sizeof(char) * (size + 1));
            if(!number)
                throw std::bad_alloc;
        } else { 
            number = (char*) malloc(sizeof(char));
            if(!number)
                throw std::bad_alloc;
        } number[size++] = num % 10;
        num /= 10;  
    }
}

BigInt::BigInt(const char* num) {
    size = 0;
    sign = true;
    char c = *num;
    if(c == '-') {
        c = *++num;
        sign = false;
    }
    while(c == '0')
        c = *++num;
    const char* str = num;
    while(c >= '0' && c <= '9') {
        c = *++num ;
        size++;
    }
    number = (char*) malloc(sizeof(char) * size);
    if(!number) {
        throw std::bad_alloc;
        size = 0;
    } for(size_t i = 0; i < size; i++) {
        c = *--num - '0';
        number[i] = c;
    }
}

BigInt::BigInt(const BigInt & A) {
    number = (char*) malloc(sizeof(char) * A.size);
    size = A.size;
    if(!number) {
        throw std::bad_alloc;
        size = 0;
    } sign = A.sign;
    memcpy(number, A.number, sizeof(char) * size);
}

BigInt::~BigInt() {
    if(size)
        free(number);
}

BigInt BigInt::operator=(const BigInt & A) {
    if(size)
        free(number);
    number = (char*) malloc(sizeof(char) * A.size);
    size = A.size;
    if(!number) {
        throw std::bad_alloc;
        size = 0;
    } sign = A.sign;
    memcpy(number, A.number, sizeof(char) * size);
    return *this;
}

BigInt BigInt::Add(const BigInt & A) const{
    BigInt temp = BigInt();
    char last = 0;
    char a, b;
    temp.number = (char*) malloc(size + 1);
    temp.size = size + 1;
    if(!number) {
        throw std::bad_alloc;
        temp.size = 0;
    } 
    for(size_t i = 0; i < size; i++) {
        a = 0;
        if(i < A.size)
            a = A.number[i];
        b = a + number[i] + last;
        last = b / 10;
        temp.number[i] = b % 10;
    }
    if(last)
        temp.number[size] = 1;
    else {
        temp.number = (char*) realloc(temp.number, size);
        temp.size--;
    }
    return temp;
}

BigInt BigInt::Sub(const BigInt & A) const{
    BigInt temp = BigInt();
    char last = 0;
    char a, b;
    temp.number = (char*) malloc(size);
    temp.size = size;
    if(!number) {
        throw std::bad_alloc;
        temp.size = 0;
    } 
    int i;
    for(i = 0; i < size; i++) {
        a = 0;
        if(i < A.size)
            a = A.number[i];
        b = number[i] - a + last;
        last = 0;
        if(b < 0) {
            last = -1;
            b += 10;
        }
        temp.number[i] = b;
    }
    i = size - 1;
    while((i >= 0) && (temp.number[i] == 0)) {
        temp.size--;
        i--;
    }
    temp.number = (char*) realloc(temp.number, temp.size);
    return temp;
}

char BigInt::tmp_same_size(const BigInt & A) const{
    size_t i = size - 1;
    while(i >= 0) {
        if(number[i] > A.number[i])
            return 1;
        if(number[i] < A.number[i])
            return -1;
        i--;
    }
    return 0;
}

BigInt BigInt::operator+(const BigInt & A) const {
    BigInt temp;
    if(sign == A.sign) {
        if(size > A.size) 
            temp = Add(A);
        else
            temp = A.Add(*this);
        temp.sign = sign;
    } else {
        if((size > A.size) || (size == A.size) && (tmp_same_size(A) > 0)) {
            temp = Sub(A);
            temp.sign = sign;
        } else {
            temp = A.Sub(*this);
            temp.sign = A.sign;
        }
    }
    return temp;
}

BigInt BigInt::operator-(const BigInt & A) const {
    return operator+(-A);
}

BigInt BigInt::operator-() const {
    BigInt temp = *this;
    temp.sign = !sign;
    return temp;
}

std::ostream & operator<<(std::ostream & out, const BigInt & A){
    if(A.size && !A.sign)
        out << '-';
    for(int i = A.size-1; i >= 0; i--)
        out << int(A.number[i]);
    if(!A.size)
        out << 0;
    return out;
}

bool BigInt::operator<(const BigInt & A) const {
    return (size < A.size) || (size == A.size) && (tmp_same_size(A) < 0);
}

bool BigInt::operator==(const BigInt & A) const {
    return (size == A.size) && !tmp_same_size(A);
}

bool BigInt::operator<=(const BigInt & A) const {
    return operator<(A) || operator==(A);
}

bool BigInt::operator>=(const BigInt & A) const {
    return !operator<(A);
}

bool BigInt::operator>(const BigInt & A) const {
    return !operator<=(A);
}

bool BigInt::operator!=(const BigInt & A) const {
    return !operator==(A);
}