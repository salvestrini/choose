#####
#
# SYNOPSIS
#
#   AX_CHECK_CURSES
#
# DESCRIPTION
#
#   Detect SysV compatible curses, such as ncurses.
#
#   Defines HAVE_CURSES_H or HAVE_NCURSES_H if curses is found.
#   CURSES_LIB is also set with the required libary, but is not
#   appended to LIBS automatically. If no working curses libary is
#   found CURSES_LIB will be left blank.
#
#   This macro adds the option "--with-ncurses" to configure which can
#   force the use of ncurses or nothing at all.
#
#   This macro is based on MP_WITH_CURSES from Mark Pulford
#
# LAST MODIFICATION
#
#   2008-02-28
#
# COPYLEFT
#
#   Copyright (c) 2008 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#   Copyright (c) 2007 Mark Pulford <mark@kyne.com.au>
#
#   This program is free software; you can redistribute it and/or
#   modify it under the terms of the GNU General Public License as
#   published by the Free Software Foundation; either version 2 of the
#   License, or (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful, but
#   WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
#   General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
#   02111-1307, USA.
#
#   As a special exception, the respective Autoconf Macro's copyright
#   owner gives unlimited permission to copy, distribute and modify the
#   configure scripts that are the output of Autoconf when processing
#   the Macro. You need not follow the terms of the GNU General Public
#   License when using or distributing such scripts, even though
#   portions of the text of the Macro appear in them. The GNU General
#   Public License (GPL) does govern all other use of the material that
#   constitutes the Autoconf Macro.
#
#   This special exception to the GPL applies to versions of the
#   Autoconf Macro released by the Autoconf Macro Archive. When you
#   make and distribute a modified version of the Autoconf Macro, you
#   may extend this special exception to the GPL to apply to your
#   modified version as well.

AC_DEFUN([AX_CHECK_CURSES],[dnl
  AC_ARG_WITH([ncurses],
      AS_HELP_STRING([--with-ncurses],
		     [Force the use of ncurses over curses],,))
  ax_save_LIBS="$LIBS"

  CURSES_LIBS=""
  
  if test "$with_ncurses" != yes
  then
    AC_CACHE_CHECK([for working curses], [ax_cv_curses],
      [LIBS="$LIBS -lcurses"
       AC_LINK_IFELSE([
         AC_LANG_PROGRAM([[
#include <curses.h>
         ]], [[
chtype a;
int b, c;

b = A_STANDOUT;
c = KEY_LEFT;
initscr();
         ]])
       ],[ax_cv_curses=yes],[ax_cv_curses=no])
    ])
    if test "$ax_cv_curses" = yes
    then
      AC_DEFINE(HAVE_CURSES_H,1,[Define to 1 if you have curses])
      CURSES_LIBS="-lcurses"
      CURSES_CFLAGS="-DCURSES_LOC=\"<ncurses.h>\""
    fi
  fi

  if test ! "$CURSES_LIBS"
  then
    AC_CACHE_CHECK([for working ncurses], [ax_cv_ncurses],
      [LIBS="$ax_save_LIBS -lncurses"
       AC_LINK_IFELSE([
         AC_LANG_PROGRAM([[
#include <ncurses.h>
         ]], [[
chtype a;
int b, c;

b = A_STANDOUT;
c = KEY_LEFT;
initscr();
         ]])
       ],[ax_cv_ncurses=yes],[ax_cv_ncurses=no])
    ])
    if test "$ax_cv_ncurses" = yes
    then
      AC_DEFINE(HAVE_NCURSES_H,1,[Define to 1 if you have ncurses])
      CURSES_LIBS="-lncurses"
      CURSES_CFLAGS="-DCURSES_LOC=\"<curses.h>\""
    fi
  fi

  LIBS="$ax_save_LIBS"
])
