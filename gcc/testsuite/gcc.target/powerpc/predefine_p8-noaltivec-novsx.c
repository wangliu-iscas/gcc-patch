/* { dg-do preprocess } */
/* Test whether the ARCH_PWR8 define remains set after disabling both altivec and vsx. */
/* { dg-options "-dM -E -mdejagnu-cpu=power8 -mno-altivec -mno-vsx" } */
/* { dg-final { scan-file predefine_p8-noaltivec-novsx.i "(^|\\n)#define _ARCH_PWR8 1($|\\n)"  } } */
/* { dg-final { scan-file-not predefine_p8-noaltivec-novsx.i "(^|\\n)#define _ARCH_PWR9 1($|\\n)" } } */
/* { dg-final { scan-file-not predefine_p8-noaltivec-novsx.i "(^|\\n)#define __VSX__ 1($|\\n)" } } */
/* { dg-final { scan-file-not predefine_p8-noaltivec-novsx.i "(^|\\n)#define __ALTIVEC__ 1($|\\n)" } } */
