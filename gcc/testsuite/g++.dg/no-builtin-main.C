/* Make sure we get warned about missing return with -fno-builtin-main. */
/* { dg-do compile } */
/* { dg-options "-Wreturn-type -ffreestanding -fno-builtin-main" } */

int main() {} /* { dg-warning "-Wreturn-type" } */
