#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.58)
AC_INIT([openvisa], [0.0.2], [madbr@sourceforge.net])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_SRCDIR([src/data.c])
AC_CONFIG_HEADER([src/config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([bzero memset strncasecmp])
AC_OUTPUT([Makefile
m4/Makefile
include/Makefile
src/Makefile
examples/Makefile
])

