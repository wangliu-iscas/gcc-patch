/* { dg-do compile } */
/* { dg-options "-O3 -fdump-tree-optimized" } */
/* { dg-final { scan-tree-dump-times "VEC_PERM_EXPR" 2 "optimized" } } */
/* For induction variable with differernt induction type(vect_step_op_add, vect_step_op_neg),
   It should't be handled in vectorizable_induction with just 1 single iv update(addition.),
   separate iv update and vec_perm are needed.  */
int
__attribute__((noipa))
foo (int* p, int c, int n)
{
  for (int i = 0; i != n; i++)
    {
      p[2* i]= i;
      p[2 * i+1] = c;
      c = -c;
    }
}
