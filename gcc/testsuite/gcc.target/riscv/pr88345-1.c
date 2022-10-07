/* { dg-do compile } */
/* { dg-options "-falign-functions=128" } */
/* { dg-final { scan-assembler-times "\.align\t7" 1 } } */

__attribute__((__cold__)) void a() {}
