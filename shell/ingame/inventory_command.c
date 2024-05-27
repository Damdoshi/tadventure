/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	"shell.h"

bool		shell_ingame_inventory_command(t_program		*prog,
					       const char * const *	params)
{
  const char	*name;
  const char	*desc;
  int		i;
  
  (void)params;
  for (i = 0; bunny_configuration_getf(prog->configuration, &name, "[].CurrentCharacter->Inventory[%d]", i); ++i)
    {
      t_bunny_configuration *cnf;

      if (!bunny_configuration_getf(prog->configuration, &cnf, "[].Items.%s", name))
	printfall(prog, "- %s\n", name);
      else
	{
	  bunny_configuration_getf(cnf, &name, "Name");
	  printfall(prog, "- %s", name);
	  if (bunny_configuration_getf(cnf, &desc, "Description"))
	    printfall(prog, ": %s.\n", desc);
	}
    }
  if (i == 0)
    printfall(prog, "You do not have any item in your inventory.\n");
  printfall(prog, "\n");
  return (true);
}

