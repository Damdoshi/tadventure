/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

t_bunny_configuration	*ingame_get_room(t_program	*prog,
					 const char	*name)
{
  t_bunny_configuration	*cnf;

  if (name == NULL)
    {
      if (!bunny_configuration_getf(prog->configuration, &cnf, "*[].CurrentCharacter"))
	{
	  printfall(prog, "Unexpected error: Cannot retrieve current character.\n");
	  return (NULL);
	}
      name = bunny_configuration_get_name(cnf);
    }
  else
    {
      if (!bunny_configuration_getf(prog->configuration, &cnf, "[].Characters.%s", name))
	{
	  printfall(prog, "Unexpected error: Cannot find character '%s'.\n", name);
	  return (NULL);
	}
    }

  if (!bunny_configuration_getf(cnf, &cnf, "*Room"))
    {
      printfall(prog, "Script error: Cannot retrieve character '%s' room.\n", name);
      return (NULL);
    }
  return (cnf);
}
