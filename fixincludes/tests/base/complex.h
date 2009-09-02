/*  DO NOT EDIT THIS FILE.

    It has been auto-edited by fixincludes from:

	"fixinc/tests/inc/complex.h"

    This had to be done to correct non-standard usages in the
    original, manufacturer supplied header file.  */



#if defined( AIX_COMPLEX_CHECK )
#define _Complex_I (__extension__ 1.0iF)

#endif  /* AIX_COMPLEX_CHECK */


#if defined( HPUX_IMAGINARY_I_CHECK )
#define _Complex_I (__extension__ 1.0iF)

#endif  /* HPUX_IMAGINARY_I_CHECK */


#if defined( IRIX_COMPLEX_CHECK )
#define _Complex_I (__extension__ 1.0iF)
#define I _Complex_I
#endif  /* IRIX_COMPLEX_CHECK */


#if defined( SOLARIS_COMPLEX_CHECK )
#define _Complex_I (__extension__ 1.0iF)
#define	complex		_Complex
#undef	I
#define	I		_Complex_I
#endif  /* SOLARIS_COMPLEX_CHECK */
