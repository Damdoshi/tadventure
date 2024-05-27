/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	"tadventure.h"

char		trimmed[1024][1024];
size_t		nbr_trimmed;

const char	*temp_trim(const char		*buf)
{
  if (buf == NULL)
    {
      nbr_trimmed = 0;
      return (NULL);
    }
  snprintf(trimmed[nbr_trimmed], sizeof(trimmed[nbr_trimmed]), "%s", buf);
  trim(trimmed[nbr_trimmed]);
  return (trimmed[nbr_trimmed++]);
}

