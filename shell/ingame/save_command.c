/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"shell.h"

bool			shell_ingame_save_command(t_program		*prog,
						  const char * const	*params)
{
  prog->game_changed = false;
  if (params == NULL || params[0] == NULL || params[1] == NULL)
    return (save(prog, "lastsave"));
  return (save(prog, params[1]));
}

