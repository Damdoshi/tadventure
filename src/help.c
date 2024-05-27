/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

int			help(void)
{
  fprintf(stderr,
	  "Usage is:\n"
	  "\n"
	  "\t./tadventure game_files+ options+\n"
	  "\t  Maximum quantity of game files is %d.\n"
	  "\t  First game file location will be used as game location.\n"
	  "\n"
	  "Options are:\n"
	  "\n"
	  "\t--display=MODE\n"
	  "\t\tSupported modes are: graphics, curses, shell and default (depends of game files, or if none specified, is shell).\n"
	  "\n",
	  NBRCELL(((t_program*)NULL)->configuration_files)
	  );
  return (EXIT_FAILURE);
}
