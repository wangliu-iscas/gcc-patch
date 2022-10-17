/* Inspired by 'libgomp.oacc-c-c++-common/nvptx-sese-1.c'.  */

/* { dg-additional-options -fdump-tree-optimized-raw }
   { dg-skip-if {} { *-*-* } { {-flto -fno-fat-lto-objects} } { } } */

#if 1
extern int
__attribute__((const))
foo (int);
#else
int
__attribute__((noinline))
foo (int x)
{
  return x & 2;
}
#endif

int f (int r)
{
  if (foo (r)) /* If this first 'if' holds...  */
    r *= 2;  /* ..., 'r' now has a zero-value lower-most bit...  */

  if (r & 1) /* ..., so this second 'if' can never hold...  */
    { /* ..., so this is unreachable.  */
#if 1
      /* In constrast, if the first 'if' does not hold ('foo (r) == 0'), the
	 second 'if' may hold, but we know ('foo' being 'const') that
	 'foo (r) == 0', so don't have to re-evaluate it here: */
      r += foo (r);
      /* Thus, if optimizing, we only ever expect one call of 'foo'.
	 { dg-final { scan-tree-dump-times {gimple_call <foo,} 1 optimized { target __OPTIMIZE__ } } }
	 { dg-final { scan-tree-dump-times {gimple_call <foo,} 2 optimized { target { ! __OPTIMIZE__ } } } }
      */
#else
      r += foo (-r);
#endif
    }

  return r;
}
