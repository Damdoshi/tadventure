/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

bool			load_game(t_program	*program)
{
  t_bunny_configuration	*tmp;
  size_t		i;

  program->configuration = NULL;
  for (i = 0; i < program->configuration_files_nbr; ++i)
    {
      tmp = bunny_open_configuration
	(program->configuration_files[i], program->configuration);
      if (!tmp)
	{
	  bunny_perror(program->configuration_files[i]);
	  if (program->configuration)
	    bunny_delete_configuration(program->configuration);
	  return (false);
	}
      program->configuration = tmp;
    }
  if (bunny_join_binary_directory(program->configuration_files[0]) == false)
    return (false);

  return (rebind_variables(program));
}

