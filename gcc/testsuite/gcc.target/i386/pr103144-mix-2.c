/* { dg-do run } */
/* { dg-options "-O2 -mavx2 -ftree-vectorize -fvect-cost-model=unlimited -mprefer-vector-width=256" } */
/* { dg-require-effective-target avx2 } */

#include "avx2-check.h"
#include <string.h>
#include "pr103144-mix-1.c"

typedef int v8si __attribute__((vector_size(32)));

#define N 34
void
avx2_test (void)
{
  int* epi32_exp = (int*) malloc (N * sizeof (int));
  int* epi32_dst = (int*) malloc (N * sizeof (int));

  __builtin_memset (epi32_exp, 0, N * sizeof (int));
  int b = 8;
  v8si init1 = __extension__(v8si) { 0, b, 1, -b, 2, b, 3, -b };
  v8si init2 = __extension__(v8si) { 4, b, 5, -b, 6, b, 7, -b };
  v8si init3 = __extension__(v8si) { 8, b, 9, -b, 10, b, 11, -b };
  v8si init4 = __extension__(v8si) { 12, b, 13, -b, 14, b, 15, -b };
  memcpy (epi32_exp, &init1, 32);
  memcpy (epi32_exp + 8, &init2, 32);
  memcpy (epi32_exp + 16, &init3, 32);
  memcpy (epi32_exp + 24, &init4, 32);
  epi32_exp[32] = 16;
  epi32_exp[33] = b;
  foo (epi32_dst, b, N / 2);
  if (__builtin_memcmp (epi32_dst, epi32_exp, N * sizeof (int)) != 0)
    __builtin_abort ();

  return;
}
