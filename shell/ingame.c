/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include			<ctype.h>
#include			"shell.h"

size_t				wtlen(const char * const	*wt)
{
  size_t			i;

  for (i = 0; wt[i] != NULL; ++i);
  return (i);
}

bool				shell_ingame(t_program		*prog)
{
  char				buffer[4096];
  static bool			cmd_set;
  static struct
  {
    const char			*command;
    bool			(*func)(t_program		*prog,
					const char * const	*params);
  }				commands[] =
    {
      {"menu", shell_ingame_menu_command},
      {"save", shell_ingame_save_command},
      {"look", shell_ingame_look_command},
      {"inventory", shell_ingame_inventory_command},
      {"debug", shell_ingame_debug_command},
      {"time", shell_ingame_time_command}
    };
  if (!cmd_set)
    {
      for (size_t i = 0; i < NBRCELL(commands); ++i)
	{
	  strcpy(buffer, commands[i].command);
	  buffer[0] = toupper(buffer[0]);
	  if ((commands[i].command = strdup(getl(prog, commands[i].command, "%s[0]", buffer))) == NULL)
	    {
	      bunny_perror("strdup");
	      return (false);
	    }
	}
      cmd_set = true;
    }
  const char		*toks[] = {" ", "\t", "\r", "\v", "\n", NULL};
  const char * const *	split;
  int			ret;
  ssize_t		rd;

  shell_prompt(prog);
  if ((rd = read(0, buffer, sizeof(buffer) - 1)) == -1)
    {
      perror("read");
      return (false);
    }
  else if (rd == 0)
    printfall(prog, "\n");
  buffer[rd] = 0;
  shell_separator(prog, '`');
  if (rd == 0)
    return (true);
  if (ingame_reword_command(prog, buffer) == false)
    return (-1);
  if ((split = bunny_split(&buffer[0], toks, true)) == NULL)
    {
      bunny_perror("split");
      return (false);
    }
  if (split[0] == NULL || *split[0] == '\0')
    {
      bunny_delete_split(split);
      return (true);
    }
  if (ingame_time_pass(prog) == -1)
    return (-1);
  for (rd = 0; rd < NBRCELL(commands); ++rd)
    if (leftmatch(buffer, commands[rd].command))
      {
	ret = commands[rd].func(prog, split);
	bunny_delete_split(split);
	return (ret);
      }
  ret = ingame_handle_action(prog, wtlen(split), split);
  bunny_delete_split(split);
  if (ret == -1)
    {
      emergency_save(prog);
      return (false);
    }
  return (true);
}
