##
## Input file for automake
##
## Copyright (C) 2008, 2009 Francesco Salvestrini
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License along
## with this program; if not, write to the Free Software Foundation, Inc.,
## 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
##

include $(top_srcdir)/Makefile.sub

AUTOMAKE_OPTIONS = subdir-objects

COMMONCFLAGS   = 
COMMONCPPFLAGS =				\
	-Wall -Werror				\
	-I$(top_srcdir)/include			\
	-I$(top_builddir)/include		\
	-I$(top_srcdir)				\
	-I$(top_builddir)
COMMONCXXFLAGS = 
COMMONLDADD    =

AM_LFLAGS = $(LEX_FLAGS)
AM_YFLAGS = $(YACC_FLAGS) -d

bin_PROGRAMS = choose-text choose-ncurses

CLEANFILES =

EXTRA_DIST =					\
	confdata.c				\
	expr.c					\
	expr.h					\
	menu.c					\
	symbol.c				\
	util.c					\
	util.h					\
	lkc.h					\
	lkc_proto.h				\
	Kconfig-language.txt			\
	lxdialog/BIG.FAT.WARNING

noinst_LIBRARIES = libzconf.a lxdialog/liblxdialog.a
lxdialog_liblxdialog_a_SOURCES =		\
	lxdialog/checklist.c			\
	lxdialog/menubox.c			\
	lxdialog/textbox.c			\
	lxdialog/yesno.c			\
	lxdialog/inputbox.c			\
	lxdialog/util.c				\
	lxdialog/msgbox.c			\
	lxdialog/colors.h			\
	lxdialog/dialog.h
lxdialog_liblxdialog_a_CPPFLAGS =		\
	$(COMMONCPPFLAGS)
lxdialog_liblxdialog_a_CFLAGS   =		\
	$(COMMONCFLAGS)				\
	$(CURSES_CFLAGS)

BUILT_SOURCES =					\
	zconf-parser.h

## Including zconf-parser.h into the libzconf_a_SOURCES variable solves
## the chicken-egg problem in the 'distcheck' target (generation of
## zconf-parser.h file)
libzconf_a_SOURCES  =				\
	lkc_defs.h				\
	zconf-parser.y				\
	zconf-scanner.l
libzconf_a_CPPFLAGS =				\
	$(COMMONCPPFLAGS)			\
	-DYY_NO_INPUT
libzconf_a_CFLAGS =				\
	$(COMMONCFLAGS)				\
	-DYY_NO_INPUT

choose_text_SOURCES  =				\
	conf.c
choose_text_CPPFLAGS = $(COMMONCPPFLAGS)
choose_text_CFLAGS   = $(COMMONCFLAGS)
choose_text_LDADD    =				\
	$(COMMONLDADD)				\
	libzconf.a 

choose_ncurses_SOURCES  =			\
	mconf.c
choose_ncurses_CPPFLAGS = $(COMMONCPPFLAGS)
choose_ncurses_CFLAGS   = $(COMMONCFLAGS)
choose_ncurses_LDADD    =			\
	$(COMMONLDADD)				\
	libzconf.a				\
	lxdialog/liblxdialog.a			\
	$(CURSES_LIBS)

lkc_defs.h: Makefile $(srcdir)/lkc_proto.h
	$(SED) < $(srcdir)/lkc_proto.h > lkc_defs.h 's/P(\([^,]*\),.*/#define \1 (\*\1_p)/'

CLEANFILES += lkc_defs.h

##
## Maintainer related targets
##
update-local: Makefile

maintainer-check-local: Makefile
