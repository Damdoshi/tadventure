/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		<stdarg.h>
#include		<stdio.h>
#include		"shell.h"

bool			printfall(t_program			*prog,
				  const char			*pattern,
				  ...)
{
  char			buffer[4096];
  va_list		lst;
  int			len;

  va_start(lst, pattern);
  len = vsnprintf(buffer, sizeof(buffer), pattern, lst);
  if (len >= (int)sizeof(buffer))
    return (false);
  return (catall(prog, buffer, len));
}

