/* Inspired by 'libgomp.oacc-c-c++-common/nvptx-sese-1.c'.  */

/* { dg-additional-options -O1 } */
/* { dg-additional-options -fdump-tree-dom3-raw } */


extern int
__attribute__((const))
foo1 (int);

int f1 (int r)
{
  if (foo1 (r)) /* If this first 'if' holds...  */
    r *= 2;  /* ..., 'r' now has a zero-value lower-most bit...  */

  if (r & 1) /* ..., so this second 'if' can never hold...  */
    { /* ..., so this is unreachable.  */
      /* In constrast, if the first 'if' does not hold ('foo1 (r) == 0'), the
	 second 'if' may hold, but we know ('foo1' being 'const') that
	 'foo1 (r) == 0', so don't have to re-evaluate it here: */
      r += foo1 (r);
      /* Thus, if optimizing, we only ever expect one call of 'foo1'.
	 { dg-final { scan-tree-dump-times {gimple_call <foo1,} 1 dom3 } } */
    }

  return r;
}


extern int
__attribute__((const))
foo2 (int);

int f2 (int r)
{
  if (foo2 (r)) /* If this first 'if' holds...  */
    r *= 2;  /* ..., 'r' now has a zero-value lower-most bit...  */

  if ((r & 2) && (r & 1)) /* ..., so 'r & 1' in this second 'if' can never hold...  */
    { /* ..., so this is unreachable.  */
      /* In constrast, if the first 'if' does not hold ('foo2 (r) == 0'), the
	 second 'if' may hold, but we know ('foo2' being 'const') that
	 'foo2 (r) == 0', so don't have to re-evaluate it here: */
      r += foo2 (r);
      /* Thus, if optimizing, we only ever expect one call of 'foo2'.
	 { dg-final { scan-tree-dump-times {gimple_call <foo2,} 1 dom3 } } */
    }

  return r;
}


extern int
__attribute__((const))
foo3 (int);

int f3 (int r)
{
  if (foo3 (r)) /* If this first 'if' holds...  */
    r *= 2;  /* ..., 'r' now has a zero-value lower-most bit...  */

  if (r & 3) /* ..., so this second 'if' can never hold...  */
    { /* ..., so this is unreachable.  */
      /* In constrast, if the first 'if' does not hold ('foo3 (r) == 0'), the
	 second 'if' may hold, but we know ('foo3' being 'const') that
	 'foo3 (r) == 0', so don't have to re-evaluate it here: */
      r += foo3 (r);
      /* Thus, if optimizing, we only ever expect one call of 'foo3'.
	 { dg-final { scan-tree-dump-times {gimple_call <foo3,} 1 dom3 { xfail *-*-* } } } */
    }

  return r;
}
