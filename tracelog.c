/*
 *  diagnostic scaffolding code
 *  2014-09-18 through ....
 *  (C) John D. Bell  (jdb@systemsartisans.com)
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or (at
 *  your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#include	"cvs.h"

static char *	tracelogfile = "cvs-fast-export.trace";
static char	errormsg[256];

FILE * tlfd = NULL;

void
start_tracelog(int ac, char ** av)
{
    int 	i;
    time_t	t;
    char	_s[256];
    char *	s = &_s[0];

    sprintf(errormsg, "!!! could not append to '%s'", tracelogfile);
    if ((tlfd = fopen(tracelogfile, "a")) == NULL) {
	perror(errormsg);
	exit(255);
    }
    t = time(NULL);
    s = ctime(&t);
    s[strlen(s)-2] = '\0';
    fprintf(tlfd, "========== %s -- ", s);
    for (i = 0; ((i < ac) && (av[i] != (char *)NULL)); i++) {
	fprintf(tlfd, "%s ", av[i]);
    }
    fprintf(tlfd, "==========\n");
}

void
trace_this(char const *format,...)
{
    va_list args;

    va_start(args, format);
    vfprintf(tlfd, format, args);
    va_end(args);
}

void
end_tracelog(void)
{
    fprintf(tlfd, "\n\n\n");
    fclose(tlfd);
}
