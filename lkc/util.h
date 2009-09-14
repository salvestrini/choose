/*
 * util.h
 *
 * (C) 2002 - 2006 Francesco Salvestrini <salvestrini@users.sourceforge.net>
 *
 */

#ifndef UTIL_H
#define UTIL_H

#if 0
#define DEBUG(F,A...) fprintf(stderr, "lkc: " F,##A)
#else
#define DEBUG(F,A...)
#endif
#define TRACE(F,A...) fprintf(stdout, "lkc: " F,##A)

#endif /* UTIL_H */
