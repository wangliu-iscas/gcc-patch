/* { dg-do compile } */
/* { dg-options "-falign-functions=128 -Os" } */
/* { dg-final { scan-assembler-times "\.align\t7" 1 } } */

void a() {}
