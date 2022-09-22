/* Tests for _FloatN / _FloatNx types: compile and execution tests for
   NaNs, SNAN macros in <float.h>.  Before including this file, define
   WIDTH as the value N; define EXT to 1 for _FloatNx and 0 for
   _FloatN.  */

#define CONCATX(X, Y) X ## Y
#define CONCAT(X, Y) CONCATX (X, Y)
#define CONCAT3(X, Y, Z) CONCAT (CONCAT (X, Y), Z)
#define CONCAT4(W, X, Y, Z) CONCAT (CONCAT (CONCAT (W, X), Y), Z)

#if EXT
# define TYPE CONCAT3 (_Float, WIDTH, x)
# define SNAN CONCAT3 (FLT, WIDTH, X_SNAN)
#else
# define TYPE CONCAT (_Float, WIDTH)
# define SNAN CONCAT3 (FLT, WIDTH, _SNAN)
#endif

#define __STDC_WANT_IEC_60559_TYPES_EXT__
#include <fenv.h>
#include <float.h>

extern void exit (int);
extern void abort (void);

volatile TYPE nans_cst = SNAN;

int
main (void)
{
  volatile TYPE r;
  r = nans_cst + nans_cst;
#if defined(__ARM_FP) && __ARM_FP == 4 && (EXT || WIDTH > 32)
  /* Arm with SP FPU does not support exceptions (see pr102017).  */
  if (fetestexcept (FE_INVALID))
#else
  if (!fetestexcept (FE_INVALID))
#endif
    abort ();
  exit (0);
}
