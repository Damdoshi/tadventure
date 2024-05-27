/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

bool			shell_menu_help_command(t_program		*prog,
						const char * const	*p)
{
  (void)p;
  printfall(prog, "Menu options are:\n"
	    "\n"
	    "\tplay - start a new game\n"
	    "\tlist - see saved games\n"
	    "\thelp - print this helper\n"
	    "\tload [file|number]? - load sent saved game, or the last one if none is precised\n"
	    "\texit - exit program\n"
	    "\n"
	    "Anywhere during your game, you can use the following commands:\n"
	    "\n"
	    "\tsave [file]? - save your game, use date if no name is given\n"
	    "\tmenu - to go back to menu\n"
	    "\n"
	    );
  return (true);
}

