/* { dg-options "-O1" } */

/* Verify there is no ICE on 32 bit environment.  */

void
he (int jn)
{
  {
    int bh[jn];
    if (jn != 0)
      goto wa;
  }
wa:;
}
