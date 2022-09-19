/* { dg-do preprocess } */
/* Test whether the ARCH_PWR7 and ARCH_PWR8 defines gets set
 * when we specify power7, plus options.
/* This is a variation of the test at issue in GCC PR 101865 */
/* { dg-options "-dM -E -mdejagnu-cpu=power7 -mno-vsx" } */
/* { dg-final { scan-file predefine_p7-novsx.i "(^|\\n)#define _ARCH_PWR7 1($|\\n)"  } } */
/* { dg-final { scan-file-not predefine_p7-novsx.i "(^|\\n)#define _ARCH_PWR8 1($|\\n)"  } } */
/* { dg-final { scan-file-not predefine_p7-novsx.i "(^|\\n)#define __VSX__ 1($|\\n)" } } */
/* { dg-final { scan-file predefine_p7-novsx.i "(^|\\n)#define __ALTIVEC__ 1($|\\n)" } } */
