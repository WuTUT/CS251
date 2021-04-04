//
// Created by wu on 2021/4/4.
//
#include "SimpleArray.h"

SimpleArray::SimpleArray(AllocationTracker* ptr)
    : mArray(ptr)
{
}
SimpleArray::~SimpleArray()
{
    delete[] mArray;
}
AllocationTracker* SimpleArray::get() const
{
    return mArray;
}
bool SimpleArray::isNonNull() const
{
    return mArray != nullptr;
}
AllocationTracker& SimpleArray::getReference(const uint32_t i) const
{
    return mArray[i];
}
void SimpleArray::swap(SimpleArray& rhs)
{
    // if(&rhs != this) { //no need to check
    /* just use std::swap to reuse code */
    //  AllocationTracker* tmp = this->mArray;
    // this->mArray = rhs.mArray;
    // rhs.mArray = tmp;
    //}

    //it's ok to visit another same object private member value
    std::swap(this->mArray, rhs.mArray);
}
void SimpleArray::reset(AllocationTracker* rhs)
{
    delete[] mArray;
    mArray = rhs;
}
AllocationTracker* SimpleArray::release()
{
    AllocationTracker* ret = mArray;
    mArray = nullptr;
    return ret;
}
