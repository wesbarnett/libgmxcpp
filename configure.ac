
AC_INIT(gmxcpp,2.0.0,[jbarnet4@tulane.edu])
AC_CONFIG_SRCDIR(src/CommandLine.cpp)
AC_CONFIG_AUX_DIR(config)
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE

#AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_FILES(src/Makefile)
AC_CONFIG_FILES(include/Makefile)
            
AC_PROG_CXX
        
AC_PROG_MAKE_SET
AC_HEADER_STDC

AC_CHECK_LIB(xdrfile, main,,AC_MSG_ERROR(This library requires the xdrfile
             library. It is currently available at gromacs.org.))
AC_CHECK_HEADERS(xdrfile/xdrfile.h,,AC_MSG_WARN(xdrfile header missing ?))
AC_CHECK_HEADERS(xdrfile/xdrfile_xtc.h,,AC_MSG_WARN(xdrfile header missing ?))

SHARED_VERSION_INFO="6:0:0"
AC_SUBST(SHARED_VERSION_INFO)

AC_PROG_LIBTOOL
LT_INIT
dnl read Makefile.in and write Makefile
AC_OUTPUT(Makefile)
