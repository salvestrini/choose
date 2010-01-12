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

EXTRA_DIST =
BUILT_SOURCES =
CLEANFILES =
MAINTAINERCLEANFILES =

include $(top_srcdir)/Makefile.top

ACLOCAL_AMFLAGS = -I tools/autotools/m4 --install

SUBDIRS =					\
	lkc					\
	tools					\
	docs

##
## NOTE:
##     Makefile.sub is automatically distributed by automake rules
##
EXTRA_DIST +=					\
	README COPYING INSTALL THANKS		\
	bootstrap .bootstrap			\
	choose.sh.in				\
	choose2h.sh.in

scripts =					\
	choose

all-local: $(scripts)

CLEANFILES += $(scripts)

sh_lib_SRC  = $(top_builddir)/tools/libs/sh/lib.sh

transform_sh_in_2_sh =				\
	{ { $(header_sh) &&			\
	    cat $(srcdir)/$$INFILE &&		\
	    $(footer_sh) } |			\
	    $(protect_sh) > $$OUTFILE ; } 

transform_sh_2_script =					\
	{ cat $$INFILE | $(do_subst) > $$OUTFILE &&	\
	  chmod +x $$OUTFILE ; }

protect_sh = { cat ; }
header_sh  = { echo "\#! @SHELL@" ; echo "" ; }
footer_sh  = { echo "" ; }

bin_SCRIPTS =					\
	choose					\
	choose2h

##
## choose
##

choose.sh: Makefile choose.sh.in
	INFILE=choose.sh.in ;			\
	OUTFILE=choose.sh ;			\
	$(transform_sh_in_2_sh) ||		\
	{ rm -f $$OUTFILE ; exit 1 ; }
CLEANFILES += choose.sh

choose: Makefile choose.sh
	INFILE=choose.sh ;			\
	OUTFILE=choose ;			\
	$(transform_sh_2_script) ||		\
	{ rm -f $$OUTFILE ; exit 1 ; }
CLEANFILES += choose

##
## choose2h
##

choose2h.sh: Makefile choose2h.sh.in
	INFILE=choose2h.sh.in ;			\
	OUTFILE=choose2h.sh ;			\
	$(transform_sh_in_2_sh) ||		\
	{ rm -f $$OUTFILE ; exit 1 ; }
CLEANFILES += choose2h.sh

choose2h: Makefile choose2h.sh
	INFILE=choose2h.sh ;			\
	OUTFILE=choose2h ;			\
	$(transform_sh_2_script) ||		\
	{ rm -f $$OUTFILE ; exit 1 ; }
CLEANFILES += choose2h

##
## Maintainer related targets
##

update-local: Makefile

maintainer-check-local: Makefile
