/**
 * @file methodcaller.hpp
 * @author <@> @NAME@
 *
 * @section DESCRIPTION
 * @FIXME@
 */

#ifndef __METHODCALLER_HPP__
# define __METHODCALLER_HPP__

#include "typelist.hpp"
#include "methodtype.hpp"
#include "tuple.hpp"

namespace b00st
{
  template<typename ReturnType, typename Class, typename List> struct MethodCaller;

  template<typename ReturnType, typename Class>
    struct MethodCaller<ReturnType, Class, TYPELIST0()>
    {
      typedef TYPELIST0() list_t;
      typedef typename MethodType<ReturnType, Class, list_t>::type method_t;

      static ReturnType call(method_t method, Class* object, Tuple<list_t>&)
      {
        return (object->*method)();
      }
    };

  template<typename ReturnType, typename Class, typename T1>
    struct MethodCaller<ReturnType, Class, TYPELIST1(T1)>
    {
      typedef TYPELIST1(T1) list_t;
      typedef typename MethodType<ReturnType, Class, list_t>::type method_t;

      static ReturnType call(method_t method, Class* object, Tuple<list_t>& args)
      {
        return (object->*method)(args.val1);
      }
    };

  template<typename ReturnType, typename Class, typename T1, typename T2>
    struct MethodCaller<ReturnType, Class, TYPELIST2(T1, T2)>
    {
      typedef TYPELIST2(T1, T2) list_t;
      typedef typename MethodType<ReturnType, Class, list_t>::type method_t;

      static ReturnType call(method_t method, Class* object, Tuple<list_t>& args)
      {
        return (object->*method)(args.val1, args.val2);
      }
    };

  template<typename ReturnType, typename Class, typename T1, typename T2, typename T3>
    struct MethodCaller<ReturnType, Class, TYPELIST3(T1, T2, T3)>
    {
      typedef TYPELIST3(T1, T2, T3) list_t;
      typedef typename MethodType<ReturnType, Class, list_t>::type method_t;

      static ReturnType call(method_t method, Class* object, Tuple<list_t>& args)
      {
        return (object->*method)(args.val1, args.val2, args.val3);
      }
    };

  template<typename ReturnType, typename Class, typename T1, typename T2, typename T3, typename T4>
    struct MethodCaller<ReturnType, Class, TYPELIST4(T1, T2, T3, T4)>
    {
      typedef TYPELIST4(T1, T2, T3, T4) list_t;
      typedef typename MethodType<ReturnType, Class, list_t>::type method_t;

      static ReturnType call(method_t method, Class* object, Tuple<list_t>& args)
      {
        return (object->*method)(args.val1, args.val2, args.val3, args.val4);
      }
    };

  template<typename ReturnType, typename Class, typename T1, typename T2, typename T3, typename T4, typename T5>
    struct MethodCaller<ReturnType, Class, TYPELIST5(T1, T2, T3, T4, T5)>
    {
      typedef TYPELIST5(T1, T2, T3, T4, T5) list_t;
      typedef typename MethodType<ReturnType, Class, list_t>::type method_t;

      static ReturnType call(method_t method, Class* object, Tuple<list_t>& args)
      {
        return (object->*method)(args.val1, args.val2, args.val3, args.val4, args.val5);
      }
    };

}

#endif /* !__METHODCALLER_HPP__ */

