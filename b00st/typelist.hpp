
#ifndef __TYPELIST_HPP__
# define __TYPELIST_HPP__

namespace b00st
{
  struct Empty;

  template<typename Head, typename Queue>
  struct TypeList
  {
    typedef Head head;
    typedef Queue queue;
  };

# define TYPELIST0()                            b00st::Empty
# define TYPELIST1(T1)                          b00st::TypeList< T1, TYPELIST0() >
# define TYPELIST2(T1, T2)                      b00st::TypeList< T1, TYPELIST1(T2) >
# define TYPELIST3(T1, T2, T3)                  b00st::TypeList< T1, TYPELIST2(T2, T3) >
# define TYPELIST4(T1, T2, T3, T4)              b00st::TypeList< T1, TYPELIST3(T2, T3, T4) >
# define TYPELIST5(T1, T2, T3, T4, T5)          b00st::TypeList< T1, TYPELIST4(T2, T3, T4, T5) >
# define TYPELIST6(T1, T2, T3, T4, T5, T6)      b00st::TypeList< T1, TYPELIST5(T2, T3, T4, T5, T6) >
# define TYPELIST7(T1, T2, T3, T4, T5, T6, T7)  b00st::TypeList< T1, TYPELIST5(T2, T3, T4, T5, T6, T7) >

  template<typename List>
  struct ListSize
  {
    enum { size = ListSize<typename List::queue>::size + 1 };
  };

  template<>
  struct ListSize<Empty>
  {
    enum { size = 0 };
  };

# define TYPELIST_SIZE(l) (b00st::ListSize<l>::size)

  template<typename List, unsigned int idx>
  struct ListAccessor
  {
    typedef typename ListAccessor<typename List::queue, idx - 1>::type type;
  };

  template<typename List>
  struct ListAccessor<List, 0>
  {
    typedef typename List::head type;
  };

# define TYPELIST_GET(l, i) b00st::ListAccessor< l, i>::type

  template<typename List, typename T> struct ListGetIndex { static const int idx = -1; };

  template<typename Head, typename Queue>
  struct ListGetIndex<TypeList<Head, Queue>, Head>
  {
    static const int idx = 0;
  };

  template<typename Head, typename Queue, typename T>
  struct ListGetIndex<TypeList<Head, Queue>, T>
  {
    private:
      static const int pos = ListGetIndex<Queue, T>::idx;

    public:
      static const int idx = (pos == -1 ? -1 : pos + 1);
  };

# define TYPELIST_GETIDX(l, T) (::b00st::ListGetIndex< l, T >::idx)


  template<typename List, typename T>
    struct IsInList
    {
      static const bool res = TYPELIST_GETIDX(List, T) != -1;
    };

# define TYPELIST_ISIN(l, T) (::b00st::IsInList<l, T>::res)

} /* ! namespace b00st */

#endif /* !__TYPELIST_HPP__ */

