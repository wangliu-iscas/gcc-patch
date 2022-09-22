/* { dg-do run { xfail { powerpc*-*-* } } } */
/* remove the xfail for powerpc when pr58684 is fixed */
/* { dg-add-options ieee } */
/* { dg-require-effective-target fenv_exceptions } */
/* { dg-skip-if "fenv" { powerpc-ibm-aix* } } */

#include <fenv.h>

extern void abort (void);
extern void exit (int);

volatile double x = __builtin_nan ("");
volatile int i;

int
main (void)
{
  i = x > __builtin_inf ();
#if defined(__ARM_FP) && __ARM_FP == 4
  /* Arm with SP FPU does not support exceptions (see pr102017).  */
  if (i != 0 || fetestexcept (FE_INVALID))
#else
  if (i != 0 || !fetestexcept (FE_INVALID))
#endif
    abort ();
}
