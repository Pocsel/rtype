
#ifndef __FUNCTIONTYPE_HPP__
# define __FUNCTIONTYPE_HPP__

#include "typelist.hpp"

namespace b00st
{

  template<typename ReturnType, typename List, unsigned int size>
  struct _FunctionType;

  template<typename ReturnType, typename List> struct _FunctionType<ReturnType, List, 0>
  {
    typedef ReturnType (*type)();
  };

  template<typename ReturnType, typename List> struct _FunctionType<ReturnType, List, 1>
  {
    typedef ReturnType (*type)(typename TYPELIST_GET(List, 0));
  };

  template<typename ReturnType, typename List> struct _FunctionType<ReturnType, List, 2>
  {
    typedef ReturnType (*type)(typename TYPELIST_GET(List, 0),
                               typename TYPELIST_GET(List, 1));
  };

  template<typename ReturnType, typename List> struct _FunctionType<ReturnType, List, 3>
  {
    typedef ReturnType (*type)(typename TYPELIST_GET(List, 0),
                               typename TYPELIST_GET(List, 1),
                               typename TYPELIST_GET(List, 2));
  };

  template<typename ReturnType, typename List> struct _FunctionType<ReturnType, List, 4>
  {
    typedef ReturnType (*type)(typename TYPELIST_GET(List, 0),
                               typename TYPELIST_GET(List, 1),
                               typename TYPELIST_GET(List, 2),
                               typename TYPELIST_GET(List, 3));
  };

  template<typename ReturnType, typename List> struct _FunctionType<ReturnType, List, 5>
  {
    typedef ReturnType (*type)(typename TYPELIST_GET(List, 0),
                               typename TYPELIST_GET(List, 1),
                               typename TYPELIST_GET(List, 2),
                               typename TYPELIST_GET(List, 3),
                               typename TYPELIST_GET(List, 4));
  };

  template<typename ReturnType, typename List> struct _FunctionType<ReturnType, List, 6>
  {
    typedef ReturnType (*type)(typename TYPELIST_GET(List, 0),
                               typename TYPELIST_GET(List, 1),
                               typename TYPELIST_GET(List, 2),
                               typename TYPELIST_GET(List, 3),
                               typename TYPELIST_GET(List, 4),
                               typename TYPELIST_GET(List, 5));
  };

  template<typename ReturnType, typename List> struct _FunctionType<ReturnType, List, 7>
  {
    typedef ReturnType (*type)(typename TYPELIST_GET(List, 0),
                               typename TYPELIST_GET(List, 1),
                               typename TYPELIST_GET(List, 2),
                               typename TYPELIST_GET(List, 3),
                               typename TYPELIST_GET(List, 4),
                               typename TYPELIST_GET(List, 5),
                               typename TYPELIST_GET(List, 6));
  };

  template<typename ReturnType, typename List>
  struct FunctionType
  {
    typedef typename _FunctionType<ReturnType, List, TYPELIST_SIZE(List)>::type type;
  };

} /* ! namespace b00st */

#endif /* !__FUNCTIONTYPE_HPP__ */

