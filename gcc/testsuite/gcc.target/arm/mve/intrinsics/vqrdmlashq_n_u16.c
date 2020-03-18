/* { dg-do compile  } */
/* { dg-require-effective-target arm_v8_1m_mve_ok } */
/* { dg-add-options arm_v8_1m_mve } */
/* { dg-additional-options "-O2" } */

#include "arm_mve.h"

uint16x8_t
foo (uint16x8_t a, uint16x8_t b, uint16_t c)
{
  return vqrdmlashq_n_u16 (a, b, c);
}

/* { dg-final { scan-assembler "vqrdmlash.s16"  }  } */

uint16x8_t
foo1 (uint16x8_t a, uint16x8_t b, uint16_t c)
{
  return vqrdmlashq (a, b, c);
}

/* { dg-final { scan-assembler "vqrdmlash.s16"  }  } */
