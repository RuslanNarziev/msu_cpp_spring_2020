#pragma once
#include <iostream>

template<class T>
class allocator {
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    pointer allocate(size_type count = 0);
    void deallocate(pointer ptr, size_type count);
    void destroy(pointer ptr);
};

template<class T>
T* allocator<T>::allocate(size_type count) {
    if(count)
        return static_cast<pointer>(::operator new(sizeof(value_type) * count));
    return nullptr;
}

template<class T>
void allocator<T>::deallocate(pointer ptr, size_type count) {
    for(size_t i = 0; i < count; i++)
        destroy(ptr + i);
    ::operator delete(ptr, sizeof(value_type) * count);
}

template<class T>
void allocator<T>::destroy(pointer ptr) {
    ptr->~value_type();
}



template <class T>
class Iterator{
    T* ptr;
    bool rev;

public:
    explicit Iterator(T* pointer, bool reverse = false);
    bool operator==(const Iterator<T> & other) const;
    bool operator!=(const Iterator<T> & other) const;
    Iterator<T>& operator++();
    Iterator<T>& operator--();
    Iterator<T> operator++(int);
    Iterator<T> operator--(int);
    Iterator<T>& operator+=(int n);
    Iterator<T>& operator-=(int n);
    Iterator<T> operator+(int n) const;
    Iterator<T> operator-(int n) const;
    T & operator*();
    const T & operator*() const;
    T & operator[](size_t n);
    const T & operator[](size_t n) const;
};

template <class T>
Iterator<T>::Iterator(T* pointer, bool reverse) {
    ptr = pointer;
    rev = reverse;
}

template <class T>
bool Iterator<T>::operator==(const Iterator<T> & other) const {
    return ptr == other.ptr;
}

template <class T>
bool Iterator<T>::operator!=(const Iterator<T> & other) const {
    return !operator==(other);
}

template <class T>
Iterator<T> & Iterator<T>::operator++() {
    if(rev)
        ptr--;
    else
        ptr++;
    return *this;
}

template <class T>
Iterator<T> & Iterator<T>::operator--() {
    if(rev)
        ptr++;
    else
        ptr--;
    return *this;
}

template <class T>
Iterator<T> Iterator<T>::operator++(int) {
    Iterator<T> temp(*this);
    if(rev)
        ptr--;
    else
        ptr++;
    return temp;
}

template <class T>
Iterator<T> Iterator<T>::operator--(int) {
    Iterator<T> temp(*this);
    if(rev)
        ptr++;
    else
        ptr--;
    return temp;
}

template <class T>
Iterator<T> & Iterator<T>::operator+=(int n) {
    if(rev)
        ptr -= n;
    else
        ptr += n;
    return *this;
}

template <class T>
Iterator<T> & Iterator<T>::operator-=(int n) {
    return operator+=(-n);
}

template <class T>
Iterator<T> Iterator<T>::operator+(int n) const {
    return Iterator(ptr + n, rev);
}

template <class T>
Iterator<T> Iterator<T>::operator-(int n) const {
    return Iterator(ptr - n, rev);
}

template <class T>
T & Iterator<T>::operator*() {
    return *ptr;
}

template <class T>
const T & Iterator<T>::operator*() const {
    return *ptr;
}

template <class T>
T & Iterator<T>::operator[](size_t n) {
    return ptr[n];
}

template <class T>
const T & Iterator<T>::operator[](size_t n) const {
    return ptr[n];
}


template<class T, class Alloc = allocator<T>>
class vector {
    Alloc alloc;
    T* ptr;
    size_t capacity;
    size_t _size;
public:
    using size_type = size_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
	using allocator_type = Alloc;
    using iterator = Iterator<T>;

    explicit vector(size_type count = 0);
    vector(size_type count, const_reference defaultValue);
    vector(std::initializer_list<value_type> init);

    reference operator[](size_t n);
    const_reference operator[](size_t n) const;
    //void push_back(value_type&& value);
    void push_back(const_reference value);
    void pop_back();
    bool empty() const;
    size_type size() const;
    iterator begin() noexcept;
    iterator rbegin() noexcept;
    iterator end() noexcept;
    iterator rend() noexcept;
    void reserve(size_type count);
    void resize(size_type count);
    void resize(size_type count, const_reference defaultValue);
    void clear() noexcept;
};

template<class T, class Alloc>
vector<T, Alloc>::vector(size_type count) {
    alloc = Alloc();
    if(count) 
        capacity = 2 * count;
    else
        capacity = 2;
    _size = count;
    ptr = alloc.allocate(capacity);
    for(size_t i = 0; i < count; i++) {
        ptr[i] = T();
    }
}

template<class T, class Alloc>
vector<T, Alloc>::vector(size_type count, const_reference defaultValue) {
    alloc = Alloc();
    if(count) 
        capacity = 2 * count;
    else
        capacity = 2;
    _size = count;
    ptr = alloc.allocate(capacity);
    for(size_t i = 0; i < count; i++) {
        ptr[i] = defaultValue;
    }
}

template<class T, class Alloc>
vector<T, Alloc>::vector(std::initializer_list<value_type> init) {
    alloc = Alloc();
    _size = init.size();
    capacity = 2 * _size;
    ptr = alloc.allocate(capacity);
    size_t i = 0;
    auto current = init.begin();
    const auto end = init.end();
    while (current != end)
        ptr[i++] = *current++;
}

template<class T, class Alloc>
T & vector<T, Alloc>::operator[](size_t n) {
    return ptr[n];
}

template<class T, class Alloc>
const T & vector<T, Alloc>::operator[](size_t n) const {
    return ptr[n];
}

template<class T, class Alloc>
void vector<T, Alloc>::push_back(const_reference value) {
    if(_size == capacity) 
        reserve(2 *capacity);
    ptr[_size++] = value; 
}

template<class T, class Alloc>
void vector<T, Alloc>::pop_back() {
    if(_size) {
        alloc.destroy(ptr + _size - 1);
        --_size;
    } else
        throw std::out_of_range("pop_back in empty vector");
}

template<class T, class Alloc>
bool vector<T, Alloc>::empty() const {
    return !_size;
}

template<class T, class Alloc>
size_t vector<T, Alloc>::size() const {
    return _size; 
}

template<class T, class Alloc>
void vector<T, Alloc>::clear() noexcept {
    for(size_t i = 0; i < _size; i++)
        alloc.destroy(ptr + i);
    _size = 0;
}

template<class T, class Alloc>
Iterator<T> vector<T, Alloc>::begin() noexcept {
    return iterator(ptr);
}

template<class T, class Alloc>
Iterator<T> vector<T, Alloc>::rbegin() noexcept {
    return iterator(ptr + _size - 1, true);
}

template<class T, class Alloc>
Iterator<T> vector<T, Alloc>::end() noexcept {
    return iterator(ptr + _size);
}

template<class T, class Alloc>
Iterator<T> vector<T, Alloc>::rend() noexcept {
    return iterator(ptr - 1, true);
}

template<class T, class Alloc>
void vector<T, Alloc>::resize(size_type count) {
    if(_size > count) 
        for(size_t i = count; i < _size; i++)
            alloc.destroy(ptr + i);
    else {
        if(count > capacity)
            reserve(2 * count);
        for(size_t i = _size; i < count; i++)
            ptr[i] = T();
    }
    _size = count;
}

template<class T, class Alloc>
void vector<T, Alloc>::resize(size_type count, const_reference defaultValue) {
    if(_size > count) 
        for(size_t i = count; i < _size; i++)
            alloc.destroy(ptr + i);
    else {
        if(count > capacity)
            reserve(2 * count);
        for(size_t i = _size; i < count; i++)
            ptr[i] = defaultValue;
    }
    _size = count;
}

template<class T, class Alloc>
void vector<T, Alloc>::reserve(size_type count) {
    if(count > capacity) {
        T* _ptr= alloc.allocate(count);
        for(size_t i = 0; i < _size; i++)
            _ptr[i] = ptr[i];
        alloc.deallocate(ptr, _size);
        ptr = _ptr;
        capacity = count;
    }
}