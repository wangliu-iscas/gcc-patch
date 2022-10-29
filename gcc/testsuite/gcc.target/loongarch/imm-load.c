/* { dg-do compile } */
/* { dg-options "-mabi=lp64d -O2 -fdump-rtl-loop2_invariant" } */

extern long long b[10];
static inline long long
repeat_bytes (void)
{
  long long r = 0x0101010101010101;

  return r;
}

static inline long long
highbit_mask (long long m)
{
  return m & repeat_bytes ();
}

void test(long long *a)
{
  for (int i = 0; i < 10; i++)
    b[i] = highbit_mask (a[i]);

}
/* { dg-final { scan-rtl-dump-times "moved without introducing a new temporary register" 4 "loop2_invariant" } } */
