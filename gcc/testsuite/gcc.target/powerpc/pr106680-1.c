/* { dg-require-effective-target lp64 } */
/* { dg-options "-mno-powerpc64" } */

/* Verify there is an error message about PowerPC64 requirement.  */

int foo ()
{
  return 1;
}

/* { dg-error "'-m64' requires a PowerPC64 cpu" "PR106680" { target powerpc*-*-linux* powerpc-*-rtems* } 0 } */
/* { dg-warning "'-maix64' requires PowerPC64 architecture remain enabled" "PR106680" { target powerpc*-*-aix* } 0 } */
