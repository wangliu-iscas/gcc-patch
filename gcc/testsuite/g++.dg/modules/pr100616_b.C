// PR c++/100616
// { dg-additional-options "-std=c++20 -fmodules-ts" }
module pr100616;

C<A{}> c2;

// FIXME: We don't reuse the artificial VAR_DECL for the class NTTP argument A{}
// from the other translation unit, which causes these types to be different.
using ty_a = decltype(c1);
using ty_a = decltype(c2); // { dg-bogus "conflicting" "" { xfail *-*-* } }
