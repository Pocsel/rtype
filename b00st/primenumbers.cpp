// génère des nombres premiers avec les erreurs g++
// Erwin Unruh (C) 2002
// http://www.erwin-unruh.de/Prim.html
//
// g++ -DLAST=101 primenumbers.cpp 2>&1| grep -E 'error:.*with' | grep -E 'i = [0-9]+' -o

#ifndef _WIN32
template <int i> struct D { D(void*); operator int(); };

template <int p, int i> struct is_prime {
 enum { prim = (p==2) || (p%i) && is_prime<(i>2?p:0), i-1> :: prim };
};

template <int i> struct Prime_print {
 Prime_print<i-1> a;
 enum { prim = is_prime<i, i-1>::prim };
 void f() { D<i> d = prim ? 1 : 0; a.f();}
};

template<> struct is_prime<0,0> { enum {prim=1}; };
template<> struct is_prime<0,1> { enum {prim=1}; };

template<> struct Prime_print<1> {
 enum {prim=0};
 void f() { D<1> d = prim ? 1 : 0; };
};

#ifndef LAST
#define LAST 18
#endif

int main() {
 Prime_print<LAST> a;
 a.f();
}
#endif
