// { dg-do compile }
// { dg-options "-O2" }
// { dg-additional-options "-mno-avx512f -march=skylake" { target { i?86-*-* x86_64-*-* } } }

#include "pr90773-1a.C"
