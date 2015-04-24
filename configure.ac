#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([todo-redmine], [0.1], [todo-redmine@fabrykowski.pl])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/todo_redmine.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([curl], [curl_global_init],[],
             [
             AC_MSG_ERROR([libcurl-dev not found])
             ])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT(Makefile src/Makefile)
