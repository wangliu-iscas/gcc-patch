/* PR c++/106937 */
/* { dg-options "-fcf-protection -w" } */

[[gnu::nocf_check]] typedef void (*FuncPointerWithNoCfCheck)(void);
typedef void (*FuncPointer)(void);
[[gnu::nocf_check]] void testNoCfCheck();
void testNoCfCheck(){};
int [[gnu::nocf_check]] i;
void testNoCfCheckImpl(double i [[gnu::nocf_check]]) {}
void testNoCfCheckMismatch(FuncPointer f) {
  FuncPointerWithNoCfCheck fNoCfCheck = f;
  (*fNoCfCheck)();
}
