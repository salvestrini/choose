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

noinst_PROGRAMS = packrules

COMMONCFLAGS   =
COMMONCPPFLAGS =				\
	-Wall -Werror				\
	-I$(top_srcdir)/lkc			\
	-I$(top_builddir)/lkc			\
	-I$(top_srcdir)				\
	-I$(top_builddir)
COMMONCXXFLAGS = 
COMMONLDADD    =

packrules_SOURCES  =				\
	packrules-stream.h			\
	packrules-stream.cxx			\
	packrules-common.h			\
	packrules-common.cxx			\
	packrules-main.cxx

packrules_CFLAGS   = $(COMMONCFLAGS)

## XXX FIXME: We should include another directory instead ...
packrules_CPPFLAGS = $(COMMONCPPFLAGS)
packrules_CXXFLAGS = $(COMMONCXXFLAGS)

FAIL_TESTS    =

SUCCESS_TESTS =

XFAIL_TESTS = $(FAIL_TESTS)

check_SCRIPTS = $(FAIL_TESTS) $(SUCCESS_TESTS)

TESTS =	$(check_PROGRAMS) $(check_SCRIPTS)

EXTRA_DIST = $(TESTS)

clean-local:

MAINTAINERCLEANFILES =

##
## Maintainer related targets
##
update-local: Makefile

maintainer-check-local: Makefile
