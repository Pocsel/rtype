
#ifndef __METHODTYPE_HPP__
# define __METHODTYPE_HPP__

namespace b00st
{

  template<typename ReturnType, typename Class, typename List, unsigned int size>
  struct _MethodType;

  template<typename ReturnType, typename Class, typename List>
  struct _MethodType<ReturnType, Class, List, 0>
  {
    typedef ReturnType (Class::*type)();
  };

  template<typename ReturnType, typename Class, typename List>
  struct _MethodType<ReturnType, Class, List, 1>
  {
    typedef ReturnType (Class::*type)(typename TYPELIST_GET(List, 0));
  };

  template<typename ReturnType, typename Class, typename List>
  struct _MethodType<ReturnType, Class, List, 2>
  {
    typedef ReturnType (Class::*type)(typename TYPELIST_GET(List, 0),
                                      typename TYPELIST_GET(List, 1));
  };

  template<typename ReturnType, typename Class, typename List>
  struct _MethodType<ReturnType, Class, List, 3>
  {
    typedef ReturnType (Class::*type)(typename TYPELIST_GET(List, 0),
                                      typename TYPELIST_GET(List, 1),
                                      typename TYPELIST_GET(List, 2));
  };

  template<typename ReturnType, typename Class, typename List>
  struct _MethodType<ReturnType, Class, List, 4>
  {
    typedef ReturnType (Class::*type)(typename TYPELIST_GET(List, 0),
                                      typename TYPELIST_GET(List, 1),
                                      typename TYPELIST_GET(List, 2),
                                      typename TYPELIST_GET(List, 3));
  };

  template<typename ReturnType, typename Class, typename List>
  struct _MethodType<ReturnType, Class, List, 5>
  {
    typedef ReturnType (Class::*type)(typename TYPELIST_GET(List, 0),
                                      typename TYPELIST_GET(List, 1),
                                      typename TYPELIST_GET(List, 2),
                                      typename TYPELIST_GET(List, 3),
                                      typename TYPELIST_GET(List, 4));
  };

  template<typename ReturnType, typename Class, typename List>
  struct _MethodType<ReturnType, Class, List, 6>
  {
    typedef ReturnType (Class::*type)(typename TYPELIST_GET(List, 0),
                                      typename TYPELIST_GET(List, 1),
                                      typename TYPELIST_GET(List, 2),
                                      typename TYPELIST_GET(List, 3),
                                      typename TYPELIST_GET(List, 4),
                                      typename TYPELIST_GET(List, 5));
  };

  template<typename ReturnType, typename Class, typename List>
  struct _MethodType<ReturnType, Class, List, 7>
  {
    typedef ReturnType (Class::*type)(typename TYPELIST_GET(List, 0),
                                      typename TYPELIST_GET(List, 1),
                                      typename TYPELIST_GET(List, 2),
                                      typename TYPELIST_GET(List, 3),
                                      typename TYPELIST_GET(List, 4),
                                      typename TYPELIST_GET(List, 5),
                                      typename TYPELIST_GET(List, 6));
  };

  template<typename ReturnType, typename Class, typename List>
  struct MethodType
  {
    typedef typename _MethodType<ReturnType, Class, List, TYPELIST_SIZE(List)>::type type;
  };
}

#endif /* !__METHODTYPE_HPP__ */

