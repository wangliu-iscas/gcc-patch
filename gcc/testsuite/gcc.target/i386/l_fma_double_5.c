/* { dg-do compile } */
/* { dg-prune-output ".*warning: 'sseregparm' attribute ignored.*" } */
/* { dg-options "-O2 -mfma" } */

/* Test that the compiler properly optimizes floating point multiply
   and add instructions into FMA3 instructions.  */

/* { dg-options "-O3 -mfma" } */


#define TYPE double

#include "l_fma_5.h"

/* { dg-final { scan-assembler-times "vfmadd132pd" 8  } } */
/* { dg-final { scan-assembler-times "vfmsub132pd" 8  } } */
/* { dg-final { scan-assembler-times "vfnmadd132pd" 8  } } */
/* { dg-final { scan-assembler-times "vfnmsub132pd" 8  } } */
/* { dg-final { scan-assembler-times "vfmadd132sd" 8  } } */
/* { dg-final { scan-assembler-times "vfmsub132sd" 8  } } */
/* { dg-final { scan-assembler-times "vfnmadd132sd" 8  } } */
/* { dg-final { scan-assembler-times "vfnmsub132sd" 8  } } */
