#include <iostream>

template<typename TYPE>
class SharedPointer
{
friend class SharedPointer;

private:
    int* pRefCount_;
    TYPE* pPtr_;
    
private:
    TYPE* getPtr();
    int* getCount();

public:
    void deletePtr();
    void reSet();
    int useCount();
    SharedPointer<TYPE> operator = (SharedPointer<TYPE> sharedPtr);
    static SharedPointer<TYPE> makeShared(TYPE type);
    static SharedPointer<TYPE> makeShared(TYPE* type);
    
public:
    //생성자
    SharedPointer(TYPE ptr);
    SharedPointer(TYPE* ptr);
    //복사 생성자
    SharedPointer(SharedPointer& other);
    ~SharedPointer();

};

template<typename TYPE>
SharedPointer<TYPE>::SharedPointer(TYPE ptr)
    : pPtr_(new TYPE(ptr)), pRefCount_(new int(1))
{
}

template<typename TYPE>
SharedPointer<TYPE>::SharedPointer(TYPE* ptr)
    : pPtr_(ptr), pRefCount_(new int(1))
{
}

template<typename TYPE>
SharedPointer<TYPE>::SharedPointer(SharedPointer& other)
{
    pPtr_ = other.getPtr();
    pRefCount_ = other.getCount();
    *pRefCount_ += 1;
}

template<typename TYPE>
SharedPointer<TYPE>::~SharedPointer()
{
    if(!pPtr_)
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
    TYPE* ptr = pPtr_;
    return ptr;
}

template<typename TYPE>
int* SharedPointer<TYPE>::getCount()
{
    int* count = pRefCount_;
    return count;
}

template<typename TYPE>
SharedPointer<TYPE> SharedPointer<TYPE>::makeShared(TYPE type)
{
    SharedPointer<TYPE> target(new TYPE(type));
    return target;
}

template<typename TYPE>
SharedPointer<TYPE> SharedPointer<TYPE>::makeShared(TYPE* type)
{
    SharedPointer<TYPE> target(type);
    return target;
}

template<typename TYPE>
void SharedPointer<TYPE>::deletePtr()
{
    delete pPtr_;
    pPtr_ = nullptr;
}

template<typename TYPE>
void SharedPointer<TYPE>::reSet()
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

struct teststruct
{
    int a = 0;
    int b = 0;

    teststruct()
    {

    }
};

class Test
{
    int a;
    int b;
    
    Test(int _a, int _b)
    :a(_a), b(_b)
    {
        
    }
}

int main()
{
    teststruct ab;
    
    std::shared_ptr<Test> testPtr = std::make_shared<Test>(6, 10);
    SharedPointer<int> testtesttest = SharedPointer<int>::makeShared(5);
    SharedPointer<int> test(4);
    SharedPointer<int> testtest(testtesttest);
    
    std::cout << test.useCount() << std::endl;
    std::cout << testtest.useCount() << std::endl;

    test.reSet();
    std::cout << test.useCount() << std::endl;
    std::cout << testtest.useCount() << std::endl;
}
