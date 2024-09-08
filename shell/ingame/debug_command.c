/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	"shell.h"

bool		shell_ingame_debug_command(t_program		*prog,
					   const char * const *	params)
{
  (void)params;
  return (bunny_save_configuration(BC_DABSIC, "/dev/stderr", prog->configuration));
}


