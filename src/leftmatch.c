/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

int			leftmatch(const char	*a,
				  const char	*b)
{
  while (*b && *a == *b)
    {
      a += 1;
      b += 1;
    }
  return (!*b);
}

