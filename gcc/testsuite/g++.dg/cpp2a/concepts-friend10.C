// { dg-do compile { target c++20 } }
// Verify we don't crash during constraint matching containing
// a TEMPLATE_ID_EXPR referring to a template from the current
// instantiation.

template<class T>
struct A {
  template<int N> static constexpr bool C = sizeof(T) > N;
  friend constexpr void f(A) requires C<3> { }
  friend constexpr void f(A) requires C<3> || true { }
};

template<class T>
struct A<T*> {
  template<int N> static constexpr bool C = sizeof(T) > N;
  friend constexpr void g(A) requires C<3> { }
  friend constexpr void g(A) requires C<3> || true { }
};

template struct A<int>;
template struct A<int*>;
