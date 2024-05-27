/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

bool			save(t_program			*prog,
			     const char			*name)
{
  char			buffer[1024];

  snprintf(buffer, sizeof(buffer), "save/%s.dab", name);
  if (bunny_save_configuration(BC_DABSIC, buffer, prog->configuration) == false)
    bunny_perror("Save failed");
  // On ne quitte pas en cas d'erreur! Peut etre que l'utilisateur peut
  // faire quelque chose...
  return (true);
}

