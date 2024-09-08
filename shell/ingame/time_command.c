/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	"shell.h"

bool		shell_ingame_time_command(t_program		*prog,
					  const char * const *	params)
{
  char		dbuffer[128];

  (void)params;
  snprintf(dbuffer, sizeof(dbuffer), "%s %d %d:%d\n",
	   language(prog, "Day"), prog->day, prog->hour, prog->minute
	   );
  return (true);
}

