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
	choose.in				\
	choose2h.in				\
	choose2python.in

bin_SCRIPTS =					\
	choose					\
	choose2h				\
	choose2python

all-local: $(bin_SCRIPTS)

CLEANFILES += $(bin_SCRIPTS)

choose: $(srcdir)/choose.in Makefile
	( rm -f $@ $@.tmp && \
	  $(do_subst) < $(srcdir)/choose.in > $@.tmp && \
	  chmod +x $@.tmp && \
	  chmod a-w $@.tmp && \
	  mv -f $@.tmp $@ ) || { \
	        rm -f $@ $@.tmp ; \
	        exit 1 ; \
	}
EXTRA_DIST += choose.in

choose2h: $(srcdir)/choose2h.in Makefile
	( rm -f $@ $@.tmp && \
	  $(do_subst) < $(srcdir)/choose2h.in > $@.tmp && \
	  chmod +x $@.tmp && \
	  chmod a-w $@.tmp && \
	  mv -f $@.tmp $@ ) || { \
	        rm -f $@ $@.tmp ; \
	        exit 1 ; \
	}
EXTRA_DIST += choose2h.in

choose2python: $(srcdir)/choose2python.in Makefile
	( rm -f $@ $@.tmp && \
	  $(do_subst) < $(srcdir)/choose2python.in > $@.tmp && \
	  chmod +x $@.tmp && \
	  chmod a-w $@.tmp && \
	  mv -f $@.tmp $@ ) || { \
	        rm -f $@ $@.tmp ; \
	        exit 1 ; \
	}
EXTRA_DIST += choose2python.in

##
## Maintainer related targets
##

update-local: Makefile

maintainer-check-local: Makefile
