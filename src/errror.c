/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	<stdarg.h>
#include	<stdio.h>

// Useful to stop with GDB
void		error(const char		*pattern,
		      ...)
{
  va_list	lst;

  va_start(lst, pattern);
  vfprintf(stderr, pattern, lst);
}

