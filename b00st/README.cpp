
#include <iostream>

#include "functor.hpp"

/** functions and classes for examples **/

void f()
{
  std::cout << "f()" << std::endl;
}

void f1(double d)
{
  std::cout << "f1("<<d<<")" << std::endl;
}

class A
{
  public:
    static int staticMethod(float f)
    {
      std::cout << "A::staticMethod("<<f<<")" << std::endl;
      return 0;
    }
    int method(float f)
    {
      std::cout << "A::method("<<f<<")" << std::endl;
      return 0;
    }

};


int main()
{

/**
 * Functor type syntax:
 *
 *  - standard functions and static methods:
 *      FUNCTOR`nbArgs`(ReturnType, arg1, arg2, ...)
 *
 *  - method functions:
 *      FUNCTOR`nbArgs`(ReturnType, arg1, arg2, ...)
 */

/**
 * declaration examples
 */
  // void f();
  FUNCTOR1(void) fun_f;

  // void f1(double);
  FUNCTOR2(void, double) fun_f1;

  // static int A::staticMethod(float)
  FUNCTOR2(int, float) A_staticMethod;

  // int A::method(float)
  FUNCTOR2(int, float) A_method;




/**
 * Binding methods:
 *
 *  - with b00st::bind method
 *
 *  - with functor constructor (same arguments as bind method)
 */

/**
 * binding examples
 */
  // void f();
  fun_f = b00st::bind(&f);

  // void f1(double);
  fun_f1 = b00st::bind(&f1);

  // static int A::staticMethod(float)
  A_staticMethod = b00st::bind(&A::staticMethod);

  // int A::method(float)
  A a;
  A_method = b00st::bind(&A::method, a); // bound with a

  /** Using our functors :) **/

  fun_f();
  fun_f1(12.012456);
  A_staticMethod(0.12f);
  A_method(0.42f);

  return 0;
}

