AC_INIT([GameOfLife], [0.0], [contact@maxenceadnot.me])
AC_PREREQ([2.60])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
if test -z $CFLAGS; then
    CFLAGS='-O2 -lncurses'
fi
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
