#pragma once
#include <iostream>

class BigInt {
public:
    char* number;
    size_t size;
    bool sign;
    BigInt Add(const BigInt & A) const;
    BigInt Sub(const BigInt & A) const;
    char tmp_same_size(const BigInt & A) const;
public:
    BigInt(long long num=0);
    BigInt(const char* num);
    BigInt(const BigInt & A);
    ~BigInt();
    BigInt operator=(const BigInt & A);
    BigInt operator+(const BigInt & A) const;
    BigInt operator-(const BigInt & A) const;
    BigInt operator-() const;
    friend std::ostream & operator<<(std::ostream & out , const BigInt & A);
    bool operator<(const BigInt & A) const;
    bool operator<=(const BigInt & A) const;
    bool operator>=(const BigInt & A) const;
    bool operator>(const BigInt & A) const;
    bool operator==(const BigInt & A) const;
    bool operator!=(const BigInt & A) const;
};