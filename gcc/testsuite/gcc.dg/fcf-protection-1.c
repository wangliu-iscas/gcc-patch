/* PR c++/106937 */
/* { dg-options "-fcf-protection" } */

[[gnu::nocf_check]] typedef void (*FuncPointerWithNoCfCheck)(void);
typedef void (*FuncPointer)(void);
[[gnu::nocf_check]] void testNoCfCheck();
void testNoCfCheck(){};
int i;
void testNoCfCheckImpl(double i) {}
void testNoCfCheckMismatch(FuncPointer f) {
  FuncPointerWithNoCfCheck fNoCfCheck = f; /* { dg-warning "initialization" } */
  (*fNoCfCheck)();
}
