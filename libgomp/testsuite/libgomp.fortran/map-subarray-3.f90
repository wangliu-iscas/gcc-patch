! { dg-do run }

module mymod
type G
integer :: x, y
integer, pointer :: arr(:)
integer :: z
end type G
end module mymod

program myprog
use mymod

integer, target :: arr1(10)
integer, target :: arr2(10)
integer, target :: arr3(10)
type(G), dimension(3) :: gvar

integer :: i, j

gvar(1)%arr => arr1
gvar(2)%arr => arr2
gvar(3)%arr => arr3

gvar(1)%arr = 0
gvar(2)%arr = 0
gvar(3)%arr = 0

i = 1
j = 2

!$omp target map(gvar(i)%arr, gvar(j)%arr, gvar(j)%arr(1:5))
gvar(i)%arr(1) = gvar(i)%arr(1) + 1
gvar(j)%arr(1) = gvar(j)%arr(1) + 2
!$omp end target

i = 2
j = 1

!$omp target map(gvar(i)%arr, gvar(j)%arr, gvar(j)%arr(1:5))
gvar(i)%arr(1) = gvar(i)%arr(1) + 3
gvar(j)%arr(1) = gvar(j)%arr(1) + 4
!$omp end target

if (gvar(i)%arr(1).ne.4) stop 1
if (gvar(j)%arr(1).ne.6) stop 2

end program myprog
