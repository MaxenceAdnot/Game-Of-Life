AC_INIT([GameOfLife], [0.0], [adnot.maxence@gmail.com])
AC_PREREQ([2.65])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
if test -z $CXXFLAGS; then
    CXXFLAGS='-O2 -lncurses -lstdc++'
fi
AC_PROG_CXX
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
