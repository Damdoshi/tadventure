/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	<time.h>
#include	"tadventure.h"

bool		emergency_save(t_program	*prog)
{
  char		buffer[64];

  snprintf(buffer, sizeof(buffer), "crashsave%ld", time(NULL));
  save(prog, buffer);
  return (false); // On s'en va en signalant une erreur
}

