// PR c++/100616
// { dg-additional-options "-std=c++20 -fmodules-ts" }
// { dg-module-cmi pr100616 }
export module pr100616;

template<auto> struct C { };
struct A { };
C<A{}> c1;
