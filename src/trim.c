/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		<ctype.h>
#include		"tadventure.h"

int			trim(char		*buf)
{
  size_t		r;
  size_t		w;
  bool			single;

  r = w = 0;
  single = false;
  while (buf[r])
    {
      if (isspace(buf[r]))
	{
	  if (single == false && w != 0)
	    buf[w++] = ' ';
	  single = true;
	}
      else
	{
	  buf[w++] = buf[r];
	  single = false;
	}
      r += 1;
    }
  buf[w] = '\0';
  return (w);
}

