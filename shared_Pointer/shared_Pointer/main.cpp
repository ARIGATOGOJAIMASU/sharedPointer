#include <iostream>
#include "SharedPointer.hpp"
#include <vector>

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
    std::vector<int> c;
    
    int a;
    int b;
 
public:
    Test(std::vector<int> _c, int _a, int _b)
    :c(_c), a(_a), b(_b)
    {
        
    }

    ~Test(){}
};


int test();



int main()
{
    {
        SharedPointer<Test> test = makeShared<Test>(std::vector<int>{1,2,3}, 2, 3);
        SharedPointer<Test> test2 = test;
    }
}
