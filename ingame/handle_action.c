/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		<sys/time.h>
#include		"tadventure.h"

static int		specific_action(t_program		*program,
					int			argc,
					const char * const	*argv,
					t_bunny_configuration	*ablock)
{
  t_bunny_configuration	*action;

  for (bunny_configuration_all_children(ablock, action))
    {
      const char	*cmd;
      const char	*addr;	    
      int		j;
      int		ret;

      if (!bunny_configuration_getf(action, NULL, "Command[0]"))
	{
	  error("Script error: Command field is missing in action %s.\n",
		bunny_configuration_get_address(action));
	  return (-1);
	}
      for (j = 0; bunny_configuration_getf(action, &cmd, "Command[%d]", j); ++j)
	{
	  bunny_configuration_addressf(action, &addr, "Command[%d]", j);
	  if ((ret = ingame_test_command(argc, argv, cmd, addr)) == -1)
	    return (-1);
	  if (ret == 0)
	    {
	      cmd = NULL;
	      continue ;
	    }
	  break ;
	}
      if (cmd)
	{
	  if (ingame_try_execute_action(program, action, argc - ret, &argv[ret]) == false)
	    return (-1);
	  return (1);
	}
    }
  return (0);
}

int			ingame_handle_action(t_program		*program,
					     int		argc,
					     const char * const	*argv)
{
  t_bunny_configuration	*action;
  int			i;

  // On commence par les objets de l'inventaire
  for (bunny_configuration_all_childrenf(program->configuration, action, "[].CurrentCharacter->Inventory"))
    {
      const char	*name = bunny_configuration_get_name(action);
      t_bunny_configuration *tmp;

      if (!bunny_configuration_getf(program->configuration, &tmp, "Items.%s.Actions", name))
	continue ;
      if ((i = specific_action(program, argc, argv, tmp)) != 0)
	return (i);
    }

  // Puis les actions du personnage
  if (bunny_configuration_getf(program->configuration, &action, "CurrentCharacter->Actions"))
    if ((i = specific_action(program, argc, argv, action)) != 0)
      return (i);

  // Puis l'action de la salle
  if (bunny_configuration_getf(program->configuration, &action, "CurrentCharacter->Room->Actions"))
    if ((i = specific_action(program, argc, argv, action)) != 0)
      return (i);

  // Puis toutes les salles
  if (bunny_configuration_getf(program->configuration, &action, "Rooms.AllRoomsAction"))
    if ((i = specific_action(program, argc, argv, action)) != 0)
      return (i);
  
  if (ingame_dont_know(program, argv[0]) == -1)
    return (-1);
  return (1);
}

