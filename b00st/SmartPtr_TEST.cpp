
#include <iostream>

#include "SmartPtr.hpp"

class BITE
{
public:
    BITE(char const* str) : _str(str)
    {
        std::cout << "Constructor  :  " << _str << std::endl;
    }
    ~BITE(void)
    {
        std::cout << "DESTRUCTION  :  " << _str << std::endl;
    }
    void LOL(void) const
    {
        std::cout << "LOL !!  :  " << _str << std::endl;
    }
private:
    char const* _str;
};

int main()
{
    {
        //Tests basiques
        b00st::SmartPtr<BITE> ptr(new BITE("BITE NUMERO 1"));
        b00st::SmartPtr<BITE>* ptr2 = new b00st::SmartPtr<BITE>(ptr);
        delete ptr2;
    }

    {
        //Test operator=
        b00st::SmartPtr<BITE>* ptr2 = new b00st::SmartPtr<BITE>;
        {
            b00st::SmartPtr<BITE> ptr;
            ptr = new BITE("BITE NUMERO 2");
            *ptr2 = ptr;
        }
        //Test LOL
        (*ptr2)->LOL();
        delete ptr2;
    }
}

