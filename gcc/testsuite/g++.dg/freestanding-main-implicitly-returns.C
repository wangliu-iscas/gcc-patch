/* Make sure main is implicitly returned from, even in freestanding. */
/* { dg-do compile } */
/* { dg-options "-Wreturn-type -ffreestanding" } */

int main() {}
