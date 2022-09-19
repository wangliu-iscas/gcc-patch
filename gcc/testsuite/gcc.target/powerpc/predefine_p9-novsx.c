/* { dg-do preprocess } */
/* Test whether the ARCH_PWR8 define remains set after disabling vsx.
   This also confirms __ALTIVEC__ remains set when VSX is disabled. */
/* This is the primary test at issue in GCC PR 101865 */
/* { dg-options "-dM -E -mdejagnu-cpu=power9 -mno-vsx" } */
/* {xfail *-*-*} */
/* { dg-final { scan-file predefine_p9-novsx.i "(^|\\n)#define _ARCH_PWR8 1($|\\n)"  } } */
/* { dg-final { scan-file predefine_p9-novsx.i "(^|\\n)#define _ARCH_PWR9 1($|\\n)"  } } */
/* { dg-final { scan-file-not predefine_p9-novsx.i "(^|\\n)#define __VSX__ 1($|\\n)" } } */
/* { dg-final { scan-file predefine_p9-novsx.i "(^|\\n)#define __ALTIVEC__ 1($|\\n)" } } */
