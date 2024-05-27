/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		<sys/time.h>
#include		"shell.h"

bool			shell_menu_play_command(t_program		*prog,
						const char * const	*p)
{
  (void)p;
  // On recharge la configuration originale - au cas ou.
  bunny_delete_configuration(prog->configuration);
  if (!(prog->configuration = bunny_open_configuration("default.dab", NULL)))
    {
      bunny_perror("Cannot load configuration default.dab");
      return (false);
    }
  rebind_variables(prog);
  prog->klondike = KINGAME;
  gettimeofday(&prog->before, NULL);
  if (shell_ingame_look_command(prog, NULL) == false)
    return (false);
  return (true);
}

