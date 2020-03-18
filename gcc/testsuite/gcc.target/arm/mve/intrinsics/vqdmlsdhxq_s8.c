/* { dg-do compile  } */
/* { dg-require-effective-target arm_v8_1m_mve_ok } */
/* { dg-add-options arm_v8_1m_mve } */
/* { dg-additional-options "-O2" } */

#include "arm_mve.h"

int8x16_t
foo (int8x16_t inactive, int8x16_t a, int8x16_t b)
{
  return vqdmlsdhxq_s8 (inactive, a, b);
}

/* { dg-final { scan-assembler "vqdmlsdhx.s8"  }  } */

int8x16_t
foo1 (int8x16_t inactive, int8x16_t a, int8x16_t b)
{
  return vqdmlsdhxq (inactive, a, b);
}

/* { dg-final { scan-assembler "vqdmlsdhx.s8"  }  } */
