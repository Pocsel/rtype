/**
 * @file tuple.hpp
 * @author <@> @NAME@
 *
 * @section DESCRIPTION
 * @FIXME@
 */

#ifndef __TUPLE_HPP__
# define __TUPLE_HPP__

#include "typelist.hpp"

namespace b00st
{
  template<typename List> struct Tuple;

  template<> struct Tuple<TYPELIST0()> {};
  template<typename T1> struct Tuple<TYPELIST1(T1)>
  {
    T1 val1;
    Tuple(T1 v1) : val1(v1) {}
  };

  template<typename T1, typename T2> struct Tuple<TYPELIST2(T1, T2)>
  {
    T1 val1;
    T2 val2;
    Tuple(T1 v1, T2 v2) : val1(v1), val2(v2) {}
  };

  template<typename T1, typename T2, typename T3> struct Tuple<TYPELIST3(T1, T2, T3)>
  {
    T1 val1;
    T2 val2;
    T3 val3;
    Tuple(T1 v1, T2 v2, T3 v3) : val1(v1), val2(v2), val3(v3) {}
  };

  template<typename T1, typename T2, typename T3, typename T4> struct Tuple<TYPELIST4(T1, T2, T3, T4)>
  {
    T1 val1;
    T2 val2;
    T3 val3;
    T4 val4;
    Tuple(T1 v1, T2 v2, T3 v3, T4 v4) : val1(v1), val2(v2), val3(v3), val4(v4) {}
  };

}

#endif /* !__TUPLE_HPP__ */

