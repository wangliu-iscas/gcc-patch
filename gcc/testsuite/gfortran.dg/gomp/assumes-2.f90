module m
  integer ::x 
  !$omp assumes contains(target) holds(x > 0.0)
  !$omp assumes absent(target) holds(0.0)
! { dg-error "HOLDS expression at .1. must be a logical expression" "" { target *-*-* } .-1 }
! { dg-error "'TARGET' directive mentioned both times in ABSENT and CONTAINS clauses in ASSUMES directive at .1." "" { target *-*-* } .-2 }
end module
