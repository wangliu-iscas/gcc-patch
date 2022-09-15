// { dg-additional-options "-fmodules-ts" }

export module x;

template<class T>
struct A {
  friend typename T::type;
  friend void f(A) { }
};
