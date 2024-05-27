/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

int			rightmatch(const char	*a,
				  const char	*b)
{
  const char		*c;

  if ((c = strstr(a, b)) == NULL)
    return (0);
  return (strlen(c) == strlen(b));
}

