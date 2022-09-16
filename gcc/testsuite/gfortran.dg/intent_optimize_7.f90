! { dg-do run }
! { dg-additional-options "-fno-inline -fno-ipa-modref -fdump-tree-optimized -fdump-tree-original" }
!
! PR fortran/41453
! Check that the INTENT(OUT) attribute causes one clobber to be emitted in
! the caller before each call to FOO or BAR in the *.original dump, and the
! initialization constants to be optimized away in the *.optimized dump,
! in the case of scalar array elements, derived type components,
! and complex real and imaginary part.

module x
implicit none
contains
  subroutine foo(a)
    integer, intent(out) :: a
    a = 42
  end subroutine foo
  subroutine bar(a)
    real, intent(out) :: a
    a = 24.0
  end subroutine bar
end module x

program main
  use x
  implicit none
  type :: t
    integer :: c
  end type t
  type(t) :: dc
  integer :: ac(3)
  complex :: xc, xd

  dc = t(123456789)
  call foo(dc%c)
  if (dc%c /= 42) stop 1

  ac = 100
  ac(2) = 987654321
  call foo(ac(2))
  if (any(ac /= [100, 42, 100])) stop 2

  xc = (12345.0, 11.0)
  call bar(xc%re)
  if (xc /= (24.0, 11.0)) stop 3

  xd = (17.0, 67890.0)
  call bar(xd%im)
  if (xd /= (17.0, 24.0)) stop 4

end program main

! { dg-final { scan-tree-dump-times "CLOBBER" 4 "original" } }
! { dg-final { scan-tree-dump "dc\\.c = {CLOBBER};" "original" } }
! { dg-final { scan-tree-dump "ac\\\[1\\\] = {CLOBBER};" "original" } }
! { dg-final { scan-tree-dump "REALPART_EXPR <xc> = {CLOBBER};" "original" } }
! { dg-final { scan-tree-dump "IMAGPART_EXPR <xd> = {CLOBBER};" "original" } }
! { dg-final { scan-tree-dump     "123456789" "original" } }
! { dg-final { scan-tree-dump-not "123456789" "optimized" { target __OPTIMIZE__ } } }
! { dg-final { scan-tree-dump     "987654321" "original" } }
! { dg-final { scan-tree-dump-not "987654321" "optimized" { target __OPTIMIZE__ } } }
! { dg-final { scan-tree-dump     "1\\.2345e\\+4" "original"  } }
! { dg-final { scan-tree-dump-not "1\\.2345e\\+4" "optimized" { target __OPTIMIZE__ } } }
! { dg-final { scan-tree-dump     "6\\.789e\\+4" "original"  } }
! { dg-final { scan-tree-dump-not "6\\.789e\\+4" "optimized" { target __OPTIMIZE__ } } }
