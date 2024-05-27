/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		<sys/time.h>
#include		"tadventure.h"

int			ingame_handle_action(t_program		*program,
					     int		argc,
					     const char * const	*argv)
{
  t_bunny_configuration	*croom;
  t_bunny_configuration	*cchar;
  t_bunny_configuration	*action;
  int			i;
  
  (void)argc;
  (void)argv;
  if (!bunny_configuration_getf(program->configuration, &cchar, "*[].CurrentCharacter"))
    {
      fprintf(stderr, "Unexpected error: Cannot retrieve current character.\n");
      return (-1);
    }
  if ((croom = ingame_get_room(program, NULL)) == NULL)
    return (-1);
  struct timeval	now;
  int			elapsed;

  gettimeofday(&now, NULL);
  program->elapsed += (elapsed = now.tv_sec - program->before.tv_sec);
  program->before = now;
  bunny_clear_configuration(program->parameters);
  if (!bunny_configuration_setf(program->parameters, elapsed, "[0]"))
    {
      fprintf(stderr, "Unexpected error: Cannot etastablish function call for time.\n");
      return (-1);
    }
  bunny_configuration_executef(croom, false, program->parameters, "TimePass");
  
  for (i = 0; bunny_configuration_getf(croom, &action, "Actions[%d]", i); ++i)
    {
      const char	*cmd;
      const char	*addr;	    
      int		j;
      int		ret;

      if (!bunny_configuration_getf(action, NULL, "Command[0]"))
	{
	  fprintf(stderr, "Script error: Command field is missing in action %s.\n",
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
	  return (0);
	}
    }
  if (ingame_dont_know(program, argv[0]) == -1)
    return (-1);
  return (0);
}

