/* Test that ASAN labels are referenced without unnecessary indirections.  */

/* { dg-do compile } */
/* { dg-options "-fPIE -O2 -fsanitize=kernel-address --param asan-stack=1" } */

extern void c (int *);

void a ()
{
  int b;
  c (&b);
}

/* { dg-final { scan-assembler {\tlarl\t%r\d+,\.LASANPC\d+} } } */
/* { dg-final { scan-assembler-not {\.LASANPC\d+@GOTOFF} } } */
