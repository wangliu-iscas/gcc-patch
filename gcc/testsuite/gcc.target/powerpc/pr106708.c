/* PR target/106708 */
/* { dg-do compile } } */
/* { dg-options "-O2 -mdejagnu-cpu=power8" } */
/* { dg-require-effective-target has_arch_ppc64 } */


#include "pr106708.h"

/* { dg-final { scan-assembler-times {\mli\M} 2 } } */
/* { dg-final { scan-assembler-times {\mlis\M} 1 } } */
/* { dg-final { scan-assembler-times {\moris\M} 1 } } */
/* { dg-final { scan-assembler-times {\mxoris\M} 2 } } */
