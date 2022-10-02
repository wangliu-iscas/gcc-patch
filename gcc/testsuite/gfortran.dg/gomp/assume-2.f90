subroutine foo (i, a)
  implicit none
  integer, value :: i
  integer :: a(:)
  integer :: j

  j = 7
  !$omp assume no_openmp, absent (target, teams,target) holds (i < 32) holds (i < 32_2)  ! { dg-error "'TARGET' directive mentioned multiple times in ABSENT clause in ASSUME directive" }
  !$omp end assume

  !$omp assume no_openmp_routines, contains (simd) contains ( simd )  ! { dg-error "'SIMD' directive mentioned multiple times in CONTAINS clause in ASSUME directive" }
  block
    !$omp simd
    do j = 1, i
      a(i) = j
    end do
  end block

  !$omp assume no_parallelism, contains (error) absent (error)  ! { dg-error "'ERROR' directive mentioned both times in ABSENT and CONTAINS clauses in ASSUME directive" }
  if (i >= 32) then
    !$omp error at (execution) message ("Should not happen")
  end if
  !$omp end assume

  !$omp assume holds (1.0)  ! { dg-error "HOLDS expression at .1. must be a logical expression" }
  !$omp end assume
end
