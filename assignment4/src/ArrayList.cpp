
#include <ArrayList.h>

//
// Created by wu on 2021/4/9.
//
template <typename T>
ArrayList<T>::ArrayList()
    : mArray(nullptr)
    , mSize(0)
    , mCapacity(0)
{
}
/**
 * swap the Array and size and capacity for purpose of strong exception guarantee
 * @tparam T
 * @param src
 */
template <typename T> void ArrayList<T>::swap(ArrayList<T>& src) noexcept
{
    if (this != &src) {
        mArray.swap(src.mArray);
        std::swap(mSize, src.mSize);
        std::swap(mCapacity, src.mCapacity);
    }
}
template <typename T>
ArrayList<T>::ArrayList(const uint32_t& size, const T& value)
    : mArray(new T[size])
    , mSize(size)
    , mCapacity(size)
{
    /*wrong code not strong exception safe
    T* tmp = new T[mSize];
    for (u_int32_t i = 0; i < mSize; i++) {
        tmp[i] = value;
    }
    mArray.reset(tmp);
    */
    std::fill(begin(), end(), value);
}
template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& src)
    : mArray(new T[src.mCapacity]) // if exception happened, then when mArray delete ,new T[] safe
                                   // delete!
    , mSize(src.mSize)
    , mCapacity(src.mCapacity)
{
    /*not exception safe!!
    T* tmp = new T[mCapacity];
    for (u_int32_t i = 0; i < mSize; i++) {
        tmp[i] = src.mArray[i];
    }
    mArray.reset(tmp);
     */
    // std::copy(src.begin(),src.end(),this->begin());
    std::copy(src.mArray.get(), src.mArray.get() + mSize, mArray.get());
}
template <typename T>
ArrayList<T>::ArrayList(ArrayList<T>&& src) noexcept
    : mArray(src.mArray.release())
    , mSize(src.mSize)
    , mCapacity(src.mCapacity)
{
    src.mSize = src.mCapacity = 0;
    // wrong code, should in base member initialization section
    // mArray.reset(src.mArray.release());
}
template <typename T> ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& src)
{
    if (this == &src) {
        return *this;
    }
    /* wrong code not strong exception safe
    mSize = src.mSize;
    mCapacity = src.mCapacity;
    T* tmp = new T[mCapacity];
    for (u_int32_t i = 0; i < mSize; i++) {
        tmp[i] = src.mArray[i];
    }
    mArray.reset(tmp);
    */
    ArrayList<T>(src).swap(*this);
    return *this;
}
template <typename T> ArrayList<T>& ArrayList<T>::operator=(ArrayList<T>&& src) noexcept
{
    if (this == &src) {
        return *this;
    }
    mSize = src.mSize;
    mCapacity = src.mCapacity;
    src.mSize = src.mCapacity = 0;
    mArray.reset(src.mArray.release());
    return *this;
}
template <typename T> const uint32_t& ArrayList<T>::add(const T& value)
{
    /*duplicated
    if (mSize == mCapacity) {
        if (mCapacity == 0) {
            mCapacity = 1;
        } else {
            mCapacity *= 2;
        }
        T* newArray = new T[mCapacity];
        for (u_int32_t i = 0; i < mSize; i++) {
            newArray[i] = mArray[i];
        }
        mArray.reset(newArray);
    }
    mArray[mSize++] = value;
    return mCapacity;
   */
    return add(mSize, value);
}
template <typename T> const uint32_t& ArrayList<T>::add(const uint32_t& index, const T& value)
{
    if (index < mCapacity && mSize < mCapacity) {
        for (u_int32_t i = mSize; i > index; i--) {
            mArray[i] = mArray[i - 1];
        }
        mArray[index] = value;
        mSize++;
        return mCapacity;
    }
    if (mCapacity == 0) {
        mCapacity = 1;
    }
    while (index >= mCapacity || mSize >= mCapacity) {
        mCapacity *= 2;
    }
    // Seems ok ??
    ScopedArray<T> tmp(new T[mCapacity]);
    // T* tmp = new T[mCapacity];
    u_int32_t min_index = std::min(index, mSize);
    // for (u_int32_t i = 0; i < min_index; i++) {
    //     tmp[i] = mArray[i];
    // }
    std::copy(mArray.get(), mArray.get() + min_index, tmp.get());
    if (min_index < mSize) {
        mSize++;
        // for (u_int32_t i = mSize; i > index; i--) {
        //     tmp[i] = mArray[i - 1];
        // }
        std::copy(mArray.get() + index, mArray.get() + mSize, tmp.get() + index + 1);
        tmp[index] = value;
    } else {
        /*should use fill algorithm
        for (u_int32_t i = min_index; i < index; i++) {
            tmp[i] = T();
        }
        */
        std::fill(tmp.get() + min_index, tmp.get() + index, T());
        tmp[index] = value;
        mSize = index + 1;
    }
    mArray.reset(tmp.release());
    return mCapacity;
}
template <typename T> void ArrayList<T>::clear()
{
    mArray.reset();
    mSize = 0;
    mCapacity = 0;
}
template <typename T> void ArrayList<T>::check_range(const uint32_t& index) const
{
    // no need to check uint32 < 0
    // if (index < 0 || index >= mSize) {
    if (index >= mSize) {
        throw std::out_of_range(std::to_string(index));
    }
}
template <typename T> const T& ArrayList<T>::get(const uint32_t& index) const
{
    // no need to check uint32 < 0
    // if (index < 0 || index >= mSize) {
    // if(index >= mSize){
    //     throw std::out_of_range(std::to_string(index));
    // }
    check_range(index);
    return mArray[index];
}
template <typename T> T& ArrayList<T>::get(const uint32_t& index)
{
    // no need to check uint32 < 0
    // if (index < 0 || index >= mSize) {
    // if(index >= mSize){
    //     throw std::out_of_range(std::to_string(index));
    // }
    check_range(index);
    return mArray[index];
}
template <typename T> bool ArrayList<T>::isEmpty() const
{
    return mSize == 0;
}
template <typename T> T& ArrayList<T>::operator[](const uint32_t& index)
{
    return mArray[index];
}
template <typename T> const T& ArrayList<T>::operator[](const uint32_t& index) const
{
    return mArray[index];
}
template <typename T> uint32_t ArrayList<T>::size() const
{
    return mSize;
}
template <typename T> void ArrayList<T>::set(const uint32_t& index, const T& value)
{
    // no need to check uint32 < 0
    // if (index < 0 || index >= mSize) {
    // if(index >= mSize){
    //     throw std::out_of_range(std::to_string(index));
    // }
    check_range(index);
    mArray[index] = value;
}
template <typename T> T ArrayList<T>::remove(const uint32_t& index)
{
    // no need for strongly exception
    check_range(index);
    T ret = mArray[index];
    std::copy(mArray.get() + index + 1, mArray.get() + mSize, mArray.get() + index);
    // for (uint32_t i = index + 1; i < mSize; i++) {
    //     mArray[i - 1] = mArray[i];
    // }
    mSize--;
    return ret;
}
template <typename T> ArrayListIterator<T> ArrayList<T>::begin()
{
    return iterator(mArray.get());
}
template <typename T> ArrayListIterator<T> ArrayList<T>::end()
{
    return iterator(mArray.get() + mSize);
}
