/* Demangler for GNU C++ - main program
   Copyright (C) 1989-2020 Free Software Foundation, Inc.
   Written by James Clark (jjc@jclark.uucp)
   Rewritten by Fred Fish (fnf@cygnus.com) for ARM and Lucid demangling
   Modified by Satish Pai (pai@apollo.hp.com) for HP demangling

   This file is part of GNU Binutils.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or (at
   your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING.  If not, write to the Free
   Software Foundation, 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

//#include "sysdep.h"
//#include "bfd.h"
//#include "libiberty.h"
#include "demangle.h"
#include <stdlib.h>
//#include "getopt.h"
//#include "safe-ctype.h"
//#include "bucomm.h"

static int flags = DMGL_PARAMS | DMGL_ANSI | DMGL_VERBOSE;
static int strip_underscore = 0;

    static void
demangle_it (char *mangled_name)
{
    char *result;
    unsigned int skip_first = 0;

    /* _ and $ are sometimes found at the start of function names
       in assembler sources in order to distinguish them from other
       names (eg register names).  So skip them here.  */
    if (mangled_name[0] == '.' || mangled_name[0] == '$')
        ++skip_first;
    if (strip_underscore && mangled_name[skip_first] == '_')
        ++skip_first;

    result = cplus_demangle (mangled_name + skip_first, flags);

    if (result == NULL)
        printf ("%s", mangled_name);
    else
    {
        if (mangled_name[0] == '.')
            putchar ('.');
        printf ("%s", result);
        free (result);
    }
}

/* Return the string of non-alnum characters that may occur
   as a valid symbol component, in the standard assembler symbol
   syntax.  */


int main (int argc, char **argv)
{
    int c;
    demangle_it (argv[1]);
    putchar ('\n');
    return 0;
}

