/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-fre1" } */

int foo (int *p, int *q)
{
  if (*p > 0 && *q > 0)
    {
      int v = *p + *q;
      if (v > 0)
        return *q;
    }
  return 0;
}

/* { dg-final { scan-tree-dump-times "known outgoing edge" 1 "fre1" } } */
