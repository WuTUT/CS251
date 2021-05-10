// @author G. Hemingway, copyright 2020 - All rights reserved

#ifndef ARRAYLISTITER_CPP
#define ARRAYLISTITER_CPP

template <typename T>
ArrayListIterator<T>::ArrayListIterator(T* ptr)
    : mPtr(ptr)
{
}

/**
 * Tests for iterator equality.
 * @param rhs The iterator to compare against.
 * @return True if *this and rhs point to the same element.
 */
template <typename T> bool ArrayListIterator<T>::operator==(const ArrayListIterator<T>& rhs) const
{
    return mPtr == rhs.mPtr;
}

/**
 * Tests for iterator inequality.
 * @param rhs The iterator to compare against.
 * @return False if *this and rhs point to the same element.
 */
template <typename T> bool ArrayListIterator<T>::operator!=(const ArrayListIterator<T>& rhs) const
{
    return mPtr != rhs.mPtr;
}

/**
 * Dereference operator.
 * @return A T & to the value pointed to by *this.
 */
template <typename T> T& ArrayListIterator<T>::operator*()
{
    return *mPtr;
}

/**
 * Dereference operator.
 * @return A constant T & to the value pointed to by *this.
 */
template <typename T> const T& ArrayListIterator<T>::operator*() const
{
    return *mPtr;
}

/**
 * Dereference operator.
 * @return A pointer to the value pointed to by *this.
 */
template <typename T> T* ArrayListIterator<T>::operator->()
{
    return mPtr;
}

/**
 * Dereference operator.
 * @return A pointer to the value pointed to by *this.
 */
template <typename T> const T* ArrayListIterator<T>::operator->() const
{
    return mPtr;
}

/**
 * Preincrement operator.
 * @return *this after the increment.
 */
template <typename T> ArrayListIterator<T>& ArrayListIterator<T>::operator++()
{
    ++mPtr;
    return *this;
}

/**
 * Postincrement operator.
 * @return The iterator before the increment.
 */
template <typename T> ArrayListIterator<T> ArrayListIterator<T>::operator++(int)
{
    ArrayListIterator<T> ret(mPtr);
    mPtr++;
    return ret;
}

/**
 * Predecrement operator.
 * @return *this after the decrement.
 */
template <typename T> ArrayListIterator<T>& ArrayListIterator<T>::operator--()
{
    --mPtr;
    return *this;
}

/**
 * Postdecrement operator.
 * @return The iterator before the decrement.
 */
template <typename T> ArrayListIterator<T> ArrayListIterator<T>::operator--(int)
{
    ArrayListIterator<T> ret(mPtr);
    mPtr--;
    return ret;
}

/**
 * Returns an iterator offset elements forward
 * @param offset distance to move forward
 * @return the moved iterator.
 */
template <typename T> ArrayListIterator<T> ArrayListIterator<T>::operator+(int offset) const
{
    return ArrayListIterator<T>(mPtr + offset);
}

/**
 * Returns an iterator offset elements backwards
 * @param offset distance to move back
 * @return the moved iterator.
 */
template <typename T> ArrayListIterator<T> ArrayListIterator<T>::operator-(int offset) const
{
    return ArrayListIterator<T>(mPtr - offset);
}

/**
 * Iterator subtraction (equivalent to pointer subtraction).
 * @param rhs Iterator to subtract
 * @return distance between iterators
 */
template <typename T> int ArrayListIterator<T>::operator-(const ArrayListIterator<T>& rhs) const
{
    return mPtr - rhs.mPtr;
}

/**
 * Increments this iterator by offset
 * @param offset distance to move forward
 * @return *this after the operation
 */
template <typename T> ArrayListIterator<T>& ArrayListIterator<T>::operator+=(const int& offset)
{
    mPtr += offset;
    return *this;
}

/**
 * Decrements this iterator by offset
 * @param offset distance to move backwards
 * @return *this after the operation.
 */
template <typename T> ArrayListIterator<T>& ArrayListIterator<T>::operator-=(const int& offset)
{
    mPtr -= offset;
    return *this;
}

/**
 * Subscript operator.
 * @param index offset from current position.
 * @return the T & to the value at the index offset from *this.
 */
template <typename T> T& ArrayListIterator<T>::operator[](const int& index)
{
    return mPtr[index];
}

/**
 * Subscript operator.
 * @param index offset from current position.
 * @return the const T & to the value at the index offset from *this.
 */
template <typename T> const T& ArrayListIterator<T>::operator[](int index) const
{
    return mPtr[index];
}

/**
 * Free function to make arithmetic addition commutative.
 *
 * @param offset offset from current position
 * @param iter array list iterator to offset
 * @return an offset ArrayListIterator
 */
template <typename T> ArrayListIterator<T> operator+(int offset, const ArrayListIterator<T>& iter)
{
    return ArrayListIterator<T>(iter + offset);
}

/************************************************************************************************/

/**
 * Tests for iterator equality.
 * @param rhs The iterator to compare against.
 * @return True if *this and rhs point to the same element.
 */
template <typename T>
bool ArrayListConstIterator<T>::operator==(const ArrayListConstIterator<T>& rhs) const
{
    return mPtr == rhs.mPtr;
}

/**
 * Tests for iterator inequality.
 * @param rhs The iterator to compare against.
 * @return False if *this and rhs point to the same element.
 */
template <typename T>
bool ArrayListConstIterator<T>::operator!=(const ArrayListConstIterator<T>& rhs) const
{
    return mPtr != rhs.mPtr;
}

/**
 * Dereference operator.
 * @return A constant reference to the value pointed to by *this.
 */
template <typename T> const T& ArrayListConstIterator<T>::operator*() const
{
    return *mPtr;
}

/**
 * Dereference operator.
 * @return A pointer to the value pointed to by *this.
 */
template <typename T> const T* ArrayListConstIterator<T>::operator->() const
{
    return mPtr;
}

/**
 * Preincrement operator.
 * @return *this after the increment.
 */
template <typename T> ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator++()
{
    ++mPtr;
    return *this;
}

/**
 * Postincrement operator.
 * @return The iterator before the increment.
 */
template <typename T> ArrayListConstIterator<T> ArrayListConstIterator<T>::operator++(int)
{
    ArrayListIterator<T> ret(mPtr);
    mPtr++;
    return ret;
}

/**
 * Predecrement operator.
 * @return *this after the decrement.
 */
template <typename T> ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator--()
{
    --mPtr;
    return *this;
}

/**
 * Postdecrement operator.
 * @return The iterator before the decrement.
 */
template <typename T> ArrayListConstIterator<T> ArrayListConstIterator<T>::operator--(int)
{
    ArrayListIterator<T> ret(mPtr);
    mPtr--;
    return ret;
}

/**
 * Returns an iterator offset elements forward
 * @param offset distance to move forward
 * @return the moved iterator.
 */
template <typename T>
ArrayListConstIterator<T> ArrayListConstIterator<T>::operator+(int offset) const
{
    return ArrayListIterator<T>(mPtr + offset);
}

/**
 * Returns an iterator offset elements backwards
 * @param offset distance to move back
 * @return the moved iterator.
 */
template <typename T>
ArrayListConstIterator<T> ArrayListConstIterator<T>::operator-(int offset) const
{
    return ArrayListIterator<T>(mPtr - offset);
}

/**
 * Iterator subtraction (equivalent to pointer subtraction).
 *
 * @param rhs an other const_iterator
 * @return difference between indices of this and rhs
 */
template <typename T>
int ArrayListConstIterator<T>::operator-(const ArrayListConstIterator<T>& rhs) const
{
    return mPtr - rhs.mPtr;
}

/**
 * Increments this iterator by offset
 * @param offset distance to move forward
 * @return *this after the operation
 */
template <typename T>
ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator+=(const int& offset)
{
    mPtr += offset;
    return *this;
}

/**
 * Decrements this iterator by offset
 * @param offset distance to move backwards
 * @return *this after the operation.
 */
template <typename T>
ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator-=(const int& offset)
{
    mPtr -= offset;
    return *this;
}

/**
 * Subscript operator.
 * @param index offset from current position.
 * @return the const reference to the value at the index offset from *this.
 */
template <typename T> const T& ArrayListConstIterator<T>::operator[](int index) const
{
    return mPtr[index];
}

/**
 * Creates an iterator pointing to the same element as the provided pointer.
 * @param ptr
 */
template <typename T> ArrayListConstIterator<T>::ArrayListConstIterator(const T* ptr)
{
    mPtr = ptr;
}

/**
 * Free function to make arithmetic addition commutative.
 */
template <typename T>
ArrayListConstIterator<T> operator+(const int32_t& offset, const ArrayListConstIterator<T>& iter)
{
    return ArrayListIterator<T>(iter + offset);
}

#endif // ARRAYLISTITER_CPP
