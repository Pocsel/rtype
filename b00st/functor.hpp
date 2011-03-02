/**
 * @file functor.hpp
 * @author <@> @NAME@
 *
 * @section DESCRIPTION
 * @FIXME@
 */

#ifndef __BOOST_FUNCTOR_HPP__
# define __BOOST_FUNCTOR_HPP__

#include "tuple.hpp"
#include "functiontype.hpp"
#include "functioncaller.hpp"
#include "methodtype.hpp"
#include "methodcaller.hpp"

namespace b00st
{

  template<typename ReturnType, typename ArgList>
  class IContainer
  {
    public:
      virtual ReturnType call(Tuple<ArgList>& args) = 0;
      virtual IContainer<ReturnType, ArgList>* clone() = 0;
  };

  template<typename ReturnType, typename ArgList>
  class FunctionContainer : public IContainer<ReturnType, ArgList>
  {
    private:
      typedef typename FunctionType<ReturnType, ArgList>::type function_t;
      function_t _function;

    public:
      FunctionContainer(function_t function) : _function(function) {}
      virtual ReturnType call(Tuple<ArgList>& args)
      {
        return FunctionCaller<ReturnType, ArgList>::call(this->_function, args);
      }
      virtual IContainer<ReturnType, ArgList>* clone()
      {
        return new FunctionContainer<ReturnType, ArgList>(this->_function);
      }
  };

  template<typename ReturnType, typename Class, typename ArgList>
  class MethodContainer : public IContainer<ReturnType, ArgList>
  {
    private:
      typedef typename MethodType<ReturnType, Class, ArgList>::type method_t;
      method_t _method;
      Class* _object;

    public:
      MethodContainer(method_t method, Class& object) : _method(method), _object(&object) {}
      virtual ReturnType call(Tuple<ArgList>& args)
      {
        return MethodCaller<ReturnType, Class, ArgList>::call(this->_method, this->_object, args);
      }

      virtual IContainer<ReturnType, ArgList>* clone()
      {
        return new MethodContainer<ReturnType, Class, ArgList>(this->_method, *this->_object);
      }

  };


  template<typename ReturnType, typename List = TYPELIST0()>
  class Functor
  {
    private:
      typedef typename FunctionType<ReturnType, List>::type function_t;
      IContainer<ReturnType, List>* _function;

    public:
      Functor() : _function(0) {}

      ~Functor()
      {
        if (this->_function != 0)
        {
          delete this->_function;
          this->_function = 0;
        }
      }

      Functor(Functor const& functor) : _function(0)
      {
        if (functor._function != 0)
          this->_function = functor._function->clone();
      }

      Functor& operator =(Functor const& functor)
      {
        if (this != &functor)
        {
          if (this->_function != 0)
          {
            delete this->_function;
            this->_function = 0;
          }
          if (functor._function != 0)
            this->_function = functor._function->clone();
        }
        return *this;
      }

      Functor(function_t function)
      {
        this->_function = new FunctionContainer<ReturnType, List>(function);
      }

      template<typename T>
      Functor(typename MethodType<ReturnType, T, List>::type method, T& object)
      {
        this->_function = new MethodContainer<ReturnType, T, List>(method, object);
      }

      ReturnType operator ()()
      {
        Tuple<TYPELIST0()> t;
        return this->_function->call(t);
      }

      template<typename T1>
      ReturnType operator ()(T1 a1)
      {
        Tuple<TYPELIST1(T1)> t(a1);
        return this->_function->call(t);
      }

      template<typename T1, typename T2>
      ReturnType operator ()(T1 a1, T2 a2)
      {
        Tuple<TYPELIST2(T1, T2)> t(a1, a2);
        return this->_function->call(t);
      }

      template<typename T1, typename T2, typename T3>
      ReturnType operator ()(T1 a1, T2 a2, T3 a3)
      {
        Tuple<TYPELIST3(T1, T2, T3)> t(a1, a2, a3);
        return this->_function->call(t);
      }

      template<typename T1, typename T2, typename T3, typename T4>
      ReturnType operator ()(T1 a1, T2 a2, T3 a3, T4 a4)
      {
        Tuple<TYPELIST4(T1, T2, T3, T4)> t(a1, a2, a3, a4);
        return this->_function->call(t);
      }
  };

# define FUNCTOR1(T1)                       b00st::Functor< T1, TYPELIST0() >
# define FUNCTOR2(T1, T2)                   b00st::Functor< T1, TYPELIST1(T2) >
# define FUNCTOR3(T1, T2, T3)               b00st::Functor< T1, TYPELIST2(T2, T3) >
# define FUNCTOR4(T1, T2, T3, T4)           b00st::Functor< T1, TYPELIST3(T2, T3, T4) >
# define FUNCTOR5(T1, T2, T3, T4, T5)       b00st::Functor< T1, TYPELIST4(T2, T3, T4, T5) >
# define FUNCTOR6(T1, T2, T3, T4, T5, T6)   b00st::Functor< T1, TYPELIST5(T2, T3, T4, T5, T6) >

/*** 0 args bindings ***/

  /// R f()
  template<typename R> FUNCTOR1(R) bind(R (*f)())
  {
    return FUNCTOR1(R)(f);
  }

  /// R C::m()
  template<typename R, typename C> FUNCTOR1(R) bind(R (C::*m)())
  {
    return FUNCTOR1(R)(m);
  }

  /// R C::m() with object
  template<typename R, typename C> FUNCTOR1(R) bind(R (C::*m)(), C& o)
  {
    return FUNCTOR1(R)(m, o);
  }

  /// R C::m() with const object
  template<typename R, typename C> FUNCTOR1(R) bind(R (C::*m)(), C const& o)
  {
    return FUNCTOR1(R)(m, o);
  }

/*** 1 args bindings ***/

  /// R f(A1)
  template<typename R, typename A1> FUNCTOR2(R, A1) bind(R (*f)(A1))
  {
    return FUNCTOR2(R, A1)(f);
  }

  /// R C::m(A1)
  template<typename R, typename C, typename A1> FUNCTOR2(R, A1) bind(R (C::*m)(A1))
  {
    return FUNCTOR2(R, A1)(m);
  }

  /// R C::m(A1) with object
  template<typename R, typename C, typename A1> FUNCTOR2(R, A1) bind(R (C::*m)(A1), C& o)
  {
    return FUNCTOR2(R, A1)(m, o);
  }

  /// R C::m(A1) with const object
  template<typename R, typename C, typename A1> FUNCTOR2(R, A1) bind(R (C::*m)(A1), C const& o)
  {
    return FUNCTOR2(R, A1)(m, o);
  }

/*** 2 args bindings ***/

  /// R f(A1, A2)
  template<typename R, typename A1, typename A2> FUNCTOR3(R, A1, A2) bind(R (*f)(A1, A2))
  {
    return FUNCTOR3(R, A1, A2)(f);
  }

  /// R C::m(A1)
  template<typename R, typename C, typename A1, typename A2> FUNCTOR3(R,  A1, A2) bind(R (C::*m)(A1, A2))
  {
    return FUNCTOR3(R, A1, A2)(m);
  }

  /// R C::m(A1) with object
  template<typename R, typename C, typename A1, typename A2> FUNCTOR3(R, A1, A2) bind(R (C::*m)(A1, A2), C& o)
  {
    return FUNCTOR3(R, A1, A2)(m, o);
  }

  /// R C::m(A1) with const object
  template<typename R, typename C, typename A1, typename A2> FUNCTOR3(R, A1, A2) bind(R (C::*m)(A1, A2), C const& o)
  {
    return FUNCTOR3(R, A1, A2)(m, o);
  }

/*** 3 args bindings ***/

  /// R f(A1, A2)
  template<typename R, typename A1, typename A2, typename A3> FUNCTOR4(R, A1, A2, A3) bind(R (*f)(A1, A2, A3))
  {
    return FUNCTOR4(R, A1, A2, A3)(f);
  }

  /// R C::m(A1)
  template<typename R, typename C, typename A1, typename A2, typename A3> FUNCTOR4(R,  A1, A2, A3) bind(R (C::*m)(A1, A2, A3))
  {
    return FUNCTOR4(R, A1, A2, A3)(m);
  }

  /// R C::m(A1) with object
  template<typename R, typename C, typename A1, typename A2, typename A3> FUNCTOR4(R, A1, A2, A3) bind(R (C::*m)(A1, A2, A3), C& o)
  {
    return FUNCTOR4(R, A1, A2, A3)(m, o);
  }

  /// R C::m(A1) with const object
  template<typename R, typename C, typename A1, typename A2, typename A3> FUNCTOR4(R, A1, A2, A3) bind(R (C::*m)(A1, A2, A3), C const& o)
  {
    return FUNCTOR4(R, A1, A2, A3)(m, o);
  }
}

#endif /* !__BOOST_FUNCTOR_HPP__ */

