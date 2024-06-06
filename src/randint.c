/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		<time.h>
#include		"tadventure.h"

int			randint(void)
{
  static bool		seed;

  if (!seed)
    srand(time(NULL));
  return (rand());
}
