//
// Created by wu on 2021/4/9.
//

#include <ScopedArray.h>

template <typename T> ScopedArray<T>::ScopedArray(T* ptr):mArray(ptr)
{
}
template <typename T> ScopedArray<T>::~ScopedArray()
{
    delete [] mArray;
}
template <typename T> T* ScopedArray<T>::get() const
{
    return mArray;
}
template <typename T> void ScopedArray<T>::swap(ScopedArray<T>& rhs)
{
    std::swap(mArray,rhs.mArray);
}
template <typename T> T* ScopedArray<T>::release()
{
    T* ret = mArray;
    mArray = nullptr;
    return ret;
}
template <typename T> void ScopedArray<T>::reset(T* rhs)
{
    if(rhs == mArray){
        return;
    }
    delete [] mArray;
    mArray = rhs;
}
template <typename T> ScopedArray<T>::operator bool() const
{
    return mArray!= nullptr;
}
template <typename T> const T& ScopedArray<T>::operator[](size_t i) const
{
    return mArray[i];
}
template <typename T> T& ScopedArray<T>::operator[](size_t i)
{
    return mArray[i];
}
