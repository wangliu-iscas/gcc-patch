/* { dg-do run } */
/* { dg-options "-O2 -ftrapping-math" } */
/* { dg-add-options ieee } */
/* { dg-require-effective-target fenv_exceptions } */

#include <fenv.h>
#include <stdlib.h>

double
x (void)
{
  double d = __builtin_inf ();
  return d / d;
}

int
main (void)
{
  double r = x ();
  if (!__builtin_isnan (r))
	abort ();
#if defined(__ARM_FP) && __ARM_FP == 4
  /* Arm with SP FPU does not support exceptions (see pr102017).  */
  if (fetestexcept (FE_INVALID))
#else
  if (!fetestexcept (FE_INVALID))
#endif
	abort ();
  exit (0);
}
