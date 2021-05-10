// @author G. Hemingway, copyright 2020 - All rights reserved

#ifndef ARRAYLIST_CPP
#define ARRAYLIST_CPP

#include <algorithm>
#include <stdexcept>

/**
 * Default constructor
 */
template <typename T>
ArrayList<T>::ArrayList()
    : mArray(nullptr)
    , mSize(0)
    , mCapacity(0)
{
}

/**
 * Creates an ArrayList of the provided size and fills it with the provided
 * value.
 * @param size size of the ArrayList to create
 * @param value value used to fill the ArrayList
 */
template <typename T>
ArrayList<T>::ArrayList(uint32_t size, const T& value)
    : mArray(new T[size])
    , mSize(size)
    , mCapacity(size)
{
    std::fill(begin(), end(), value);
}

/**
 * Creates a deep copy of the provided ArrayList
 * @param src ArrayList to copy
 */
template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& src)
    : mArray(new T[src.mCapacity])
    , mSize(src.mSize)
    , mCapacity(src.mCapacity)
{
    std::copy(src.begin(), src.end(), begin());
}

/**
 * Performs move constructor semantics on the provided ArrayList
 * @param src ArrayList to move
 */
template <typename T>
ArrayList<T>::ArrayList(ArrayList<T>&& src) noexcept
    : mArray(src.mArray.release())
    , mSize(src.size)
    , mCapacity(src.mCapacity)
{
    src.mCapacity = src.mSize = 0;
}

/**
 * Makes *this a deep copy of the provided ArrayList.
 * @param src ArrayList to copy
 * @return *this for chaining
 */
template <typename T> ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& src)
{
    if (this == &src) {
        return *this;
    }
    ArrayList<T>(src).swap(*this);
    return *this;
}

/**
 * Performs move assignment semantics on the provided ArrayList.
 * @param src ArrayList to move
 * @return *this for chaining
 */
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

/**
 * Adds the provided element to the end of this ArrayList.
 * @param value value to add
 */
template <typename T> uint32_t ArrayList<T>::add(const T& value)
{
    return add(mSize, value);
}

/**
 * Inserts the specified value into this ArrayList at the specified index.
 * The object is inserted before any previous element at the specified
 * location. If this ArrayList needs to be enlarged, default values are used
 * to fill the gaps up to mSize.
 * @param index location at which to insert the new element
 * @param value the element to insert
 */
template <typename T> uint32_t ArrayList<T>::add(uint32_t index, const T& value)
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

/**
 * Clears this ArrayList, leaving it empty.
 */
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
/**
 * Returns a const T & to the element stored at the specified index.
 * If the index is out of bounds, std::out_of_range is thrown with the index
 * as its message.
 * @param index the desired location
 * @return a const T & to the desired element.
 */
template <typename T> const T& ArrayList<T>::get(uint32_t index) const
{
    check_range(index);
    return mArray[index];
}

/**
 * Returns a T & to the element stored at the specified index.
 * If the index is out of bounds, std::out_of_range is thrown with the index
 * as its message.
 * @param index the desired location
 * @return a T & to the desired element.
 */
template <typename T> T& ArrayList<T>::get(uint32_t index)
{
    check_range(index);
    return mArray[index];
}

/**
 * Returns a T & to the element stored at the specified index.
 * No range checking is performed.
 * @param index the desired location
 * @return a T & to the desired element.
 */
template <typename T> T& ArrayList<T>::operator[](uint32_t index)
{
    return mArray[index];
}

/**
 * Returns a const T & to the element stored at the specified index.
 * No range checking is performed.
 * @param index the desired location
 * @return a const T & to the desired element.
 */
template <typename T> const T& ArrayList<T>::operator[](uint32_t index) const
{
    return mArray[index];
}

/**
 * Empty check.
 * @return True if this ArrayList is empty and false otherwise.
 */
template <typename T> bool ArrayList<T>::isEmpty() const
{
    return mSize == 0;
}

/**
 * Returns iterator to the beginning; in this case, a random access iterator
 * @return an iterator to the beginning of this ArrayList.
 */
template <typename T> ArrayListIterator<T> ArrayList<T>::begin()
{
    return iterator(mArray.get());
}

/**
 * Returns the past-the-end iterator of this ArrayList.
 * @return a past-the-end iterator of this ArrayList.
 */
template <typename T> ArrayListIterator<T> ArrayList<T>::end()
{
    return iterator(mArray.get() + mSize);
}

/**
 * Returns const iterator to the beginning; in this case, a random access
 * iterator
 * @return an const iterator to the beginning of this ArrayList.
 */
template <typename T> typename ArrayList<T>::const_iterator ArrayList<T>::begin() const
{
    return const_iterator(mArray.get());
}

/**
 * Returns the past-the-end const iterator of this ArrayList.
 * @return a past-the-end const iterator of this ArrayList.
 */
template <typename T> typename ArrayList<T>::const_iterator ArrayList<T>::end() const
{
    return const_iterator(mArray.get() + mSize);
}

/**
 * Removes an element at the specified location from this ArrayList and
 * returns it. Elements following index are shifted down. If index is out of
 * range, std::out_of_range is thrown with index as its message.
 * @param index the desired location
 * @return a copy of the removed element.
 */
template <typename T> void ArrayList<T>::remove(uint32_t index)
{
    check_range(index);
    T ret = mArray[index];
    std::copy(mArray.get() + index + 1, mArray.get() + mSize, mArray.get() + index);
    // for (uint32_t i = index + 1; i < mSize; i++) {
    //     mArray[i - 1] = mArray[i];
    // }
    mSize--;
    return ret;
}

/**
 * Sets the element at the desired location to the specified value. If index
 * is out of range, std::out_of_range is thrown with index as its message.
 * @param index the location to change
 * @param value the new value of the specified element.
 */
template <typename T> void ArrayList<T>::set(uint32_t index, const T& value)
{
    check_range(index);
    mArray[index] = value;
}

/**
 * Returns the size of this ArrayList.
 * @return the size of this ArrayList.
 */
template <typename T> uint32_t ArrayList<T>::size() const
{
    return mSize;
}

/**
 * Perform an exception-safe swap of the contents of *this with src.
 */
template <typename T> void ArrayList<T>::swap(ArrayList<T>& src) noexcept
{
    if (this != &src) {
        mArray.swap(src.mArray);
        std::swap(mSize, src.mSize);
        std::swap(mCapacity, src.mCapacity);
    }
}

#endif // ARRAYLIST_CPP
