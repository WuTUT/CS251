//
// Created by wu on 2021/4/9.
//

#ifndef SCOPED_ARRAY_H
#define SCOPED_ARRAY_H
#include "AllocationTracker.h"
template <typename T>
class ScopedArray {
public:
    explicit ScopedArray(T* ptr = nullptr);
    ScopedArray(const ScopedArray<T>& rhs) = delete;
    const ScopedArray<T>& operator= (const ScopedArray<T>& rhs) = delete;
    virtual ~ScopedArray();
    T* get() const;
    void swap(ScopedArray<T>& rhs);
    T* release();
    void reset(T* rhs = nullptr);
    explicit operator bool() const;
    const T& operator[] (size_t i) const;
    T& operator[] (size_t i);
private:
    T* mArray;

};
#include "../src/ScopedArray.cpp"

#endif // SCOPED_ARRAY_H
