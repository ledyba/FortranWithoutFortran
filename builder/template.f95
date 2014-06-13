module a
	interface
		subroutine f (z) bind(c)
			use iso_c_binding
			type(c_ptr), value :: z
		end subroutine
	end interface
	type G
		procedure(f), pointer, nopass :: x
	end type
	type J
		integer, pointer :: x
	end type
end module

program b
	use iso_c_binding
	use a
	implicit none;
		type (J), pointer :: x(:);
		real(8),pointer :: dbl(:);
		type(G), pointer :: p
		integer, pointer :: d(:)
		integer :: i
		integer :: n
		allocate( x(1) )
		allocate( dbl(10000000) )
		allocate( d(10000000) )
		dbl = 0;

#include "prog.f95.in"
		call c_f_pointer(C_LOC( x(1) ), p)
#include "load.f95"
		call p%x( c_loc(dbl(1)) )
		n = int(dbl(1))
		do i=2, n+1
			write (*,*), i, dbl(i)
		end do
		deallocate ( d )
		deallocate ( x )
		deallocate ( dbl )
contains
end program
