/* Test C2x variadic functions with no named parameters.  Execution tests.  */
/* { dg-do run } */
/* { dg-options "-std=c2x -pedantic-errors" } */

#include <stdarg.h>

extern void abort (void);
extern void exit (int);

double
f (...)
{
  va_list ap;
  va_start (ap);
  double ret = va_arg (ap, int);
  ret += va_arg (ap, double);
  ret += va_arg (ap, int);
  ret += va_arg (ap, double);
  va_end (ap);
  return ret;
}

void
g (...)
{
  va_list ap;
  va_start (ap, random ! ignored, ignored ** text);
  for (int i = 0; i < 10; i++)
    if (va_arg (ap, double) != i)
      abort ();
  va_end (ap);
}

int
main ()
{
  if (f (1, 2.0, 3, 4.0) != 10.0)
    abort ();
  g (0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  g (0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
  exit (0);
}
