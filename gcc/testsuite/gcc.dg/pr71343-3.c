/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-optimized" } */

int foo(int a, int b)
{
  return (a << 2) + (b << 2);
}

int bar(int a, int b)
{
  return (a << 2) + (b << 2) == (a + b) << 2;
}

/* { dg-final { scan-tree-dump-times " << " 1 "optimized" } } */
/* { dg-final { scan-tree-dump-times "return 1" 1 "optimized" } } */
