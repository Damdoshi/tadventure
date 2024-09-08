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
  printfall(prog, "%s:\n\n", getl(prog, "Menu options are", "MenuOptionsAre"));
  printfall(prog, "\t%s - %s\n",
	    getl(prog, "play", "Play[0]"),
	    getl(prog, "start a new game", "Play[1]")
	    );
  printfall(prog, "\t%s - %s\n",
	    getl(prog, "list", "List[0]"),
	    getl(prog, "see saved games", "List[1]")
	    );
  printfall(prog, "\t%s - %s\n",
	    getl(prog, "help", "Help[0]"),
	    getl(prog, "print this helper", "Help[1]")
	    );
  printfall(prog, "\t%s %s - %s\n",
	    getl(prog, "load", "Load[0]"),
	    getl(prog, "[file|number]?", "Load[1]"),
	    getl(prog, "load sent saved game, or the last one if none is precised", "Load[2]")
	    );
  printfall(prog, "\t%s - %s\n",
	    getl(prog, "exit", "Exit[0]"),
	    getl(prog, "exit program", "Exit[1]")
	    );
  printfall(prog, "\n");
  printfall(prog, "%s:\n\n",
	    getl(prog, "Anywhere during your game, you can use the following commands", "GameOptionsMessage")
	    );
  printfall(prog, "\t%s %s - %s\n",
	    getl(prog, "save", "Save[0]"),
	    getl(prog, "[file]?", "Save[1]"),
	    getl(prog, "save your game, use date if no name is given", "Save[2]")
	    );
  printfall(prog, "\t%s - %s\n",
	    getl(prog, "menu", "Menu[0]"),
	    getl(prog, "go back to menu", "Menu[1]")
	    );
  return (true);
}

