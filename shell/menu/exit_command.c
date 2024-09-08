/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	"shell.h"

bool		shell_menu_exit_command(t_program		*prog,
					const char * const	*p)
{
  (void)p;
  printfall(prog, "%s.\n", getl(prog, "Bye", "Bye"));
  prog->klondike = KLAST;
  return (true);
}
