/* Skip this on aix, otherwise it emits the error message like "64-bit
   computation with 32-bit addressing not yet supported" on aix.  */
/* { dg-skip-if "" { powerpc*-*-aix* } } */
/* { dg-require-effective-target ilp32 } */
/* { dg-options "-mpowerpc64 -m32 -O2" } */

/* Verify option -m32 doesn't override option -mpowerpc64.
   If option -mpowerpc64 gets overridden, the assembly would
   end up with addc and adde.  */
/* { dg-final { scan-assembler-not "addc" } } */
/* { dg-final { scan-assembler-not "adde" } } */

long long foo (long long a, long long b)
{
  return a+b;
}
