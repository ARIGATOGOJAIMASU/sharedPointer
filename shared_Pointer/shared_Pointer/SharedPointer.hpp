//
//  SharedPointer.hpp
//  shared_Pointer
//
//  Created by CD-a8389742a on 2023/04/20.
//

#ifndef SharedPointer_hpp
#define SharedPointer_hpp
#include <iostream>

template<typename TYPE> class SharedPointer;

template<typename TYPE, typename... Args>
static SharedPointer<TYPE> makeShared(Args ...args)
{
    SharedPointer<TYPE> target(new TYPE(args...));
    return target;
}

template<typename TYPE>
class SharedPointer
{
private:
    int* pRefCount_ = nullptr;
    TYPE* pPtr_ = nullptr;
    
private:
    int* getCount();
    void deletePtr();

public:
    TYPE* getPtr();
    void reset();
    int useCount();
    SharedPointer<TYPE> operator = (SharedPointer<TYPE> sharedPtr);
    
public:
    //생성자
    SharedPointer() = default;
    SharedPointer(TYPE* ptr);
    //복사 생성자

    SharedPointer(const SharedPointer& other);
    ~SharedPointer();
};

template<typename TYPE>
SharedPointer<TYPE>::SharedPointer(TYPE* ptr)
    : pPtr_(ptr), pRefCount_(new int(1))
{
}

template<typename TYPE>
SharedPointer<TYPE>::SharedPointer(const SharedPointer& other)
    : pPtr_(other.pPtr_), pRefCount_(other.pRefCount_)
{
    *pRefCount_ += 1;
}

template<typename TYPE>
SharedPointer<TYPE>::~SharedPointer()
{
    if(pPtr_ == nullptr)
        return;
    
    //자신이 마지막 참조일시 메모리 해제
    if(*pRefCount_ != 1)
    {
        //마지막이 아닐 시 카운트만 줄인다.
        *pRefCount_ -= 1;
        return;
    }
    
    deletePtr();

    delete pRefCount_;
    pRefCount_ = nullptr;
}

template<typename TYPE>
TYPE* SharedPointer<TYPE>::getPtr()
{
    return pPtr_;
}

template<typename TYPE>
int* SharedPointer<TYPE>::getCount()
{
    return *pRefCount_;
}

template<typename TYPE>
void SharedPointer<TYPE>::deletePtr()
{
    delete pPtr_;
    pPtr_ = nullptr;
}

template<typename TYPE>
void SharedPointer<TYPE>::reset()
{
    if (pPtr_ == nullptr)
        return;

    *pRefCount_ -= 1;

    if (pRefCount_ != 0)
    {
        pRefCount_ = nullptr;
        pPtr_ = nullptr;
        return;
    }
    
    deletePtr();
}

template<typename TYPE>
int SharedPointer<TYPE>::useCount()
{
    int count = pPtr_ == nullptr ? 0 : *pRefCount_;
    return count;
}

template<typename TYPE>
SharedPointer<TYPE> SharedPointer<TYPE>::operator=(SharedPointer<TYPE> sharedPtr)
{
    return SharedPointer(sharedPtr);
}




#endif /* SharedPointer_hpp */
