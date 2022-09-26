// { dg-do compile { target c++11 } }
int _ħ;
const char * operator ""_ħ (const char *, unsigned long);
bool operator ""_ħ (unsigned long long x);
#pragma GCC poison _ħ
bool b = 1_ħ; // This currently is allowed, is that intended?
const char *x = "hbar"_ħ; // { dg-error "attempt to use poisoned" }
