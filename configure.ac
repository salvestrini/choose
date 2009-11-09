# Process this file with autoconf to produce a configure script.

#
# configure.ac
#
# Copyright (C) 2008, 2009 Francesco Salvestrini
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

AC_INIT([Choose],
        m4_esyscmd([tools/maint/git-version-gen .tarball-version]),
        [salvestrini@gmail.com],
        [choose],
        [...])

# Check for a recent version of autoconf
AC_PREREQ(2.64)

# Place/find all autotools related files in the following directories
AC_CONFIG_SRCDIR([choose.sh.in])
AC_CONFIG_AUX_DIR([tools/autotools])
AC_CONFIG_MACRO_DIR([tools/autotools/m4])
AC_CONFIG_HEADERS([lkc/config.h])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

#
# For automake options (AM_INIT_AUTOMAKE options) see Makefile.am
# file, AUTOMAKE_OPTIONS variable
#
AM_INIT_AUTOMAKE([1.10 foreign no-installman no-installinfo -Wall nostdinc])

#
# Checks for needed programs
#

AC_PROG_GREP
AC_PROG_SED
AC_PROG_INSTALL
AC_PROG_MKDIR_P

AX_PATH_MISSING([PERL], [perl])
AX_PATH_MISSING([WGET], [wget])
AX_PATH_MISSING([DNT],  [dnt])

# C Preprocessor
AC_PROG_CPP

# C compiler
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CXX
AC_PROG_CXX_C_O
AC_PROG_CXXCPP

AC_PROG_RANLIB
#AC_PROG_LIBTOOL

#
# Lex (Flex) is needed in the tools directory
#
AM_PROG_LEX
LEX_FLAGS=""
# Use short options for compatibility (-v=--verbose, -d=--debug)
AX_PROG_FLEX([
  LEX_FLAGS="$LEX_FLAGS -v"
  AS_IF([test "x$enable_build_tools_debug" = "xyes"],[
    LEX_FLAGS="$LEX_FLAGS -d"
  ])
])
AC_SUBST(LEX_FLAGS)

#
# Yacc (Bison) is needed in the tools directory
#
AC_PROG_YACC
YACC_FLAGS=""
# Use short options for compatibility (-v=--verbose, -t=--debug)
AX_PROG_BISON([
  YACC_FLAGS="$YACC_FLAGS -v"
  AS_IF([test "x$enable_build_tools_debug" = "xyes"],[
    YACC_FLAGS="$YACC_FLAGS -t"
  ])
])
AC_SUBST(YACC_FLAGS)

#
# LKC support
#
#with_curses=yes
#MP_WITH_CURSES
AX_CHECK_CURSES
AC_SUBST(CURSES_LIBS)
AC_SUBST(CURSES_CFLAGS)

#
# Finally output the configuration
#
AC_CONFIG_FILES([
	Makefile
	docs/Makefile
	lkc/Makefile
	tools/Makefile
	tools/maint/Makefile
	tools/autotools/Makefile
	tools/autotools/m4/Makefile
])

AC_CONFIG_FILES([tools/maint/fetch],               [chmod +x tools/maint/fetch])
AC_CONFIG_FILES([tools/maint/whitespace-detect],   [chmod +x tools/maint/whitespace-detect])
AC_CONFIG_FILES([tools/maint/gitlog-to-committers],[chmod +x tools/maint/gitlog-to-committers])
AC_CONFIG_FILES([tools/maint/gittag-to-date],      [chmod +x tools/maint/gittag-to-date])
AC_CONFIG_FILES([tools/maint/guards-check],        [chmod +x tools/maint/guards-check])

AC_OUTPUT
