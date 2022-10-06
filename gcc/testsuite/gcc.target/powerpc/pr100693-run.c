/* { dg-do run { target { powerpc*-*-linux* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } } */
/* { dg-require-effective-target powerpc_vsx_ok } */
/* { dg-options "-mdejagnu-cpu=power7 -O3" } */

/* Test case for the addg6s builtin, exercising both
   unsigned int and unsigned long long arguments.  */

#include <stdio.h>
#include <stdlib.h>

unsigned int test_addg6s_int (unsigned int a, unsigned int b)
{
    return __builtin_addg6s (a, b);
}

unsigned long long test_addg6s_longlong (unsigned long long a, unsigned long long b)
{
    return __builtin_addg6s (a, b);
}

/* Table of expected values.  */

unsigned int exp_i[] = {
0x66666660,
0x66666606,
0x66666066,
0x66660666,
0x66606666,
0x66066666,
0x60666666,
0x06666666,
0x77777777
};

unsigned long long exp_ll[] = {
0x6666666666666660,
0x6666666666666606,
0x6666666666666066,
0x6666666666660666,
0x6666666666606666,
0x6666666666066666,
0x6666666660666666,
0x6666666606666666,
0x6666666066666666,
0x6666660666666666,
0x6666606666666666,
0x6666066666666666,
0x6660666666666666, 
0x6606666666666666, 
0x6066666666666666, 
0x0666666666666666, 
0x7777777777777777
};

int main() {
	unsigned int intresult;
	unsigned long long longresult;
	int idx;
	int fail=0;

	for (idx=0; idx<8; idx++) {
	   intresult = test_addg6s_int (0x01<<4*idx, 0x0f<<4*idx);
	   if (exp_i[idx] != intresult)
	      printf("index:%2d Got:%8x Expected:%8x %d\n",
			idx, intresult, exp_i[idx], ++fail);
	}

	for (idx=0; idx<16; idx++) {
	   longresult = test_addg6s_longlong (0x01ULL<<4*idx, 0x0fULL<<4*idx);
	   if (exp_ll[idx] != longresult)
	      printf("index:%2d Got:%16llx Expected:%16llx %d\n",
			idx, longresult, exp_ll[idx], ++fail);
	}
	if (fail)
		abort();
}

