#pragma once

#include "Misc/Logger.h"

#include <cstring>


template<typename T>
class vector {
public:
    vector() {}

    vector(size_t cap)
        : mSize(0)
        , mCapacity(cap)
        , mData(nullptr)
    {
        mData = new T[mCapacity];
    }

    vector(vector const &other)
        : mSize(other.mSize)
        , mCapacity(other.mCapacity)
        , mData(nullptr)
    {
        mData = new T[mCapacity];
        memcpy(mData, other.mData, mSize*sizeof(T));
    };

    ~vector() {
        clear();
    };

    vector &operator=(vector const &other) {
        delete[] mData;
        mSize = other.mSize;
        mCapacity = other.mCapacity;
        mData =  new T[mCapacity];
        memcpy(mData, other.mData, mSize*sizeof(T));
        return *this;
    };

    void push_back(const T& x) {
        if (mCapacity == mSize)
            resize();
        mData[mSize++] = x;
    };

    void erase(size_t idx) {
        if(idx >= mSize)
            return;
        const auto temp = mData[idx];
        mData[idx] = mData[--mSize];
        mData[mSize] = temp;
    }

    void eraseKeepOrder(size_t idx) {
        if(idx >= mSize)
            return;
        for (; idx < mSize; idx++) {
            mData[idx] = mData[idx + 1];
        }
        mSize--;
    }

    size_t size() const {
        return mSize;
    }

    T const &operator[](size_t idx) const {
        return mData[idx];
    }

    T& operator[](size_t idx) {
        return mData[idx];
    }

    bool isInsideBounds(size_t idx) {
        return mSize && idx < mSize;
    }

    void clear() {
        delete[] mData;
        mData = nullptr;
    }

private:
    void resize() {
        mCapacity = mCapacity ? mCapacity*2 : 1;
        T* newData = new T[mCapacity];

        // ESP crashes if data is a shared_ptr, will have to look into this one
        //memcpy(newData, mData, mSize * sizeof(T));

        // will resort to one by one assignment
        for (size_t i = 0; i < mSize; i++) {
            newData[i] = mData[i];
        }
        delete[] mData;
        mData = newData;
    };

    size_t mSize{ 0 };
    size_t mCapacity{ 0 };
    T* mData { nullptr };

};
