#include<stdio.h>
#include "demangle.h"
#include "cp-demangle.h"

int strip_underscore = 0;
static int flags = DMGL_PARAMS | DMGL_ANSI | DMGL_VERBOSE;
static void demangle_it (char *mangled_name)
{
    char *result;
    unsigned int skip_first = 0;
    size_t opt;
    /* _ and $ are sometimes found at the start of function names
       in assembler sources in order to distinguish them from other
       names (eg register names).  So skip them here.  */
    if (mangled_name[0] == '.' || mangled_name[0] == '$')
        ++skip_first;
    if (strip_underscore && mangled_name[skip_first] == '_')
        ++skip_first;

    result = cplus_demangle (mangled_name + skip_first,flags);
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

int main(void)
{   char *mangled="_Z14timedReductionPKfPfPl";
    demangle_it(mangled);
}
