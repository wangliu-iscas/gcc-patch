/* PR target/106708 */
/* { dg-do run } */
/* { dg-options "-O2" } */

#include "pr106708.h"

long long arr[] = {0x98765432ULL, 0xffffffff7cdeab55ULL, 0xffffffff65430000ULL};
int
main ()
{
  long long a[3];

  foo (a);
  if (__builtin_memcmp (a, arr, sizeof (arr)) != 0)
    __builtin_abort ();
  return 0;
}
