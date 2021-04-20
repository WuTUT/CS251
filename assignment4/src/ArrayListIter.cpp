
#include <ArrayListIter.h>

//
// Created by wu on 2021/4/20.
//
template <typename T> bool ArrayListIterator<T>::operator==(const ArrayListIterator<T>& rhs) const
{
    return mPtr == rhs.mPtr;
}
template <typename T> bool ArrayListIterator<T>::operator!=(const ArrayListIterator<T>& rhs) const
{
    return mPtr != rhs.mPtr;
}
template <typename T> T& ArrayListIterator<T>::operator*()
{
    return *mPtr;
}
template <typename T> const T& ArrayListIterator<T>::operator*() const
{
    return *mPtr;
}
template <typename T> T* ArrayListIterator<T>::operator->()
{
    return mPtr;
}
template <typename T> const T* ArrayListIterator<T>::operator->() const
{
    return mPtr;
}
template <typename T> ArrayListIterator<T>& ArrayListIterator<T>::operator++()
{
    ++mPtr;
    return *this;
}
template <typename T> ArrayListIterator<T> ArrayListIterator<T>::operator++(int)
{
    ArrayListIterator<T> ret(mPtr);
    mPtr++;
    return ret;
}
template <typename T> ArrayListIterator<T>& ArrayListIterator<T>::operator--()
{
    --mPtr;
    return *this;
}
template <typename T> ArrayListIterator<T> ArrayListIterator<T>::operator--(int)
{
    ArrayListIterator<T> ret(mPtr);
    mPtr--;
    return ret;
}
template <typename T> ArrayListIterator<T> ArrayListIterator<T>::operator+(int offset) const
{
    return ArrayListIterator<T>(mPtr + offset);
}
template <typename T> ArrayListIterator<T> ArrayListIterator<T>::operator-(int offset) const
{
    return ArrayListIterator<T>(mPtr - offset);
}
template <typename T> int ArrayListIterator<T>::operator-(const ArrayListIterator<T>& rhs) const
{
    return mPtr - rhs.mPtr;
}
template <typename T> ArrayListIterator<T>& ArrayListIterator<T>::operator+=(const int& offset)
{
    mPtr += offset;
    return *this;
}
template <typename T> ArrayListIterator<T>& ArrayListIterator<T>::operator-=(const int& offset)
{
    mPtr -= offset;
    return *this;
}

template <typename T> ArrayListIterator<T>::ArrayListIterator(T* ptr)
{
    mPtr = ptr;
}

template <typename X> ArrayListIterator<X> operator+(int offset, const ArrayListIterator<X>& iter)
{
    return ArrayListIterator<X>(iter + offset);
}
template <typename T> T& ArrayListIterator<T>::operator[](const int& index)
{
    return mPtr[index];
}
template <typename T> const T& ArrayListIterator<T>::operator[](int index) const
{
    return mPtr[index];
}
