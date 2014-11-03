AC_INIT(src/CommandLine.cpp,1.0.0)
AM_INIT_AUTOMAKE(tar-ustar)
AM_PROG_LIBTOOL

AC_CONFIG_FILES(src/Makefile)
AC_CONFIG_FILES(include/Makefile)
            
dnl find and test the C compiler
AC_PROG_CXX
AC_LANG_CPLUSPLUS

AC_PROG_CC
AC_LANG_C
        
AC_PROG_MAKE_SET
               
AC_HEADER_STDC
AC_CHECK_FUNC(atol,,AC_MSG_ERROR(oops! no atol ?!?))

AC_CHECK_LIB(xdrfile, main,,AC_MSG_ERROR(This library requires the xdrfile
             library. It is currently available at gromacs.org.))
AC_CHECK_HEADERS(xdrfile/xdrfile.h,,AC_MSG_WARN(xdrfile header missing ?))
AC_CHECK_HEADERS(xdrfile/xdrfile_xtc.h,,AC_MSG_WARN(xdrfile header missing ?))

SHARED_VERSION_INFO="0:0:0"
AC_SUBST(SHARED_VERSION_INFO)

dnl read Makefile.in and write Makefile
AC_OUTPUT(Makefile)
