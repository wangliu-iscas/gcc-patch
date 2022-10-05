// PR c++/107085
// { dg-do compile { target c++11 } }

// Must be non-trivial to exhibit the ICE.
struct X {
  X();
  X(X&&);
};
struct Z : X {};
X x1 = Z();
X x2 = X(Z());

// ...but let's try the trivial path in build_over_call as well.
struct B { };
struct D : B { };
B b1 = D();
B b2 = B(D());
