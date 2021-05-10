// @author G. Hemingway, copyright 2020 - All rights reserved

#ifndef SCOPEDARRAY_CPP
#define SCOPEDARRAY_CPP

template <class T>
ScopedArray<T>::ScopedArray(T* rhs)
    : array(rhs)
{
}

template <typename T> ScopedArray<T>::~ScopedArray()
{
    delete[] array;
}

template <typename T> T* ScopedArray<T>::get() const
{
    return array;
}

template <typename T> const T& ScopedArray<T>::operator[](std::uint32_t pos) const
{
    return array[pos];
}

template <typename T> T& ScopedArray<T>::operator[](std::uint32_t pos)
{
    return array[pos];
}

template <typename T> ScopedArray<T>::operator bool() const
{
    return array != nullptr;
}

template <typename T> void ScopedArray<T>::swap(ScopedArray& rhs)
{
    std::swap(array, rhs.array);
}

template <typename T> T* ScopedArray<T>::release()
{
    T* ret = array;
    array = nullptr;
    return ret;
}

template <typename T> void ScopedArray<T>::reset(T* rhs)
{
    if (rhs == array) {
        return;
    }
    delete array;
    array = rhs;
}

#endif // SCOPEDARRAY_CPP
