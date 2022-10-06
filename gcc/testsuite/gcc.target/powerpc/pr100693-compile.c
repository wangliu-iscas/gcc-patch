/* { dg-do compile { target { powerpc*-*-linux* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } } */
/* { dg-require-effective-target powerpc_vsx_ok } */
/* { dg-options "-mdejagnu-cpu=power7 -O3" } */
/* { dg-final { scan-assembler-times {\maddg6s\M} 4 } } */
/* { dg-final { scan-assembler-not    "bl __builtin" } } */

/* Test case for the addg6s builtin, exercising both
   unsigned int and unsigned long long arguments. */

unsigned long long test2_ull (unsigned long long a, unsigned long long b)
{
    return __builtin_addg6s (a, b);
}

unsigned int test1_ui (unsigned int a, unsigned int b)
{
    return __builtin_addg6s (a, b);
}

unsigned int test3_ui (unsigned int *a, unsigned int *b)
{
	return __builtin_addg6s(*a, *b);
}

unsigned long long test4_ull (unsigned long long *a, unsigned long long *b)
{
	return __builtin_addg6s(*a, *b);
}

