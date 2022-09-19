/* { dg-do run } */
/* { dg-require-effective-target powerpc_p9vector_ok } */
/* { dg-require-effective-target lp64 } */
/* { dg-options "-mdejagnu-cpu=power8 -mvsx -O2" } */

/* Ensure that if we set a pragma gcc target for an
   older processor, we do not compile builtins that
   the older target does not support.  */

#include <altivec.h>
#include <stdio.h>
#include <stdlib.h>

volatile int power8_set;
volatile int vsx_set;

void reset_values() {
	vsx_set=0;
	power8_set=0;
}

void test_default() {
	reset_values();
#ifdef _ARCH_PWR8
	power8_set=1;
#endif
#ifdef __VSX__
	vsx_set=1;
#endif
}

#pragma GCC target "no-vsx"
void test_no_vsx() {
	reset_values();
#ifdef _ARCH_PWR8
	power8_set=1;
#endif
#ifdef __VSX__
	vsx_set=1;
#endif
}

#pragma GCC reset_options
void test_reset_options() {
	reset_values();
#ifdef _ARCH_PWR8
	power8_set=1;
#endif
#ifdef __VSX__
	vsx_set=1;
#endif
}

int main (int argc, char *argv []) {
	test_default();
	if (!power8_set) {
	       	printf("_ARCH_PWR8 is not set.\n");
		abort();
	}
	if (!vsx_set) {
		printf("__VSX__ is not set.\n");
		abort();
	}
	test_no_vsx();
	if (!power8_set) {
		printf("_ARCH_PWR8 is not set.\n");
		abort();
	}
	if (vsx_set) {
	       	printf("__VSX__ is unexpectedly set.\n");
		abort();
	}
	test_reset_options();
	if (!power8_set) {
		printf("_ARCH_PWR8 is not set.\n");
		abort();
	}
	if (!vsx_set) {
		printf("__VSX__ is not set.\n");
		abort();
	}
}

