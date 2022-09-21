/* { dg-do compile } */
/* { dg-options "-mdejagnu-cpu=power8 -O2" } */
/* { dg-require-effective-target powerpc_p8vector_ok } */
/* { dg-final { scan-assembler "vspltisw" } } */
/* { dg-final { scan-assembler "vupkhsw" } } */
/* { dg-final { scan-assembler-not "lvx" } } */

#include <altivec.h>

vector unsigned long long
foo ()
{
  return vec_splats ((unsigned long long) 12);
}
