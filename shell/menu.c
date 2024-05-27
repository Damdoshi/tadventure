/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include			<limits.h>
#include			"tadventure.h"
#include			"shell.h"

bool				shell_menu(t_program		*prog)
{
  static const struct
  {
    const char			*command;
    bool			(*func)(t_program		*prog,
					const char * const	*params);
  }				commands[] =
    {
      {"exit", shell_menu_exit_command},
      {"play", shell_menu_play_command},
      {"list", shell_menu_list_command},
      {"load", shell_menu_load_command},
      {"help", shell_menu_help_command}
    };
  char			buffer[1024];
  ssize_t		rd;
  const char		*toks[] = {" ", "\t", "\r", "\v", "\n", NULL};
  const char * const *	split;
  bool			ret;
  
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
    return (shell_menu_exit_command(prog, NULL));
  if ((split = bunny_split(&buffer[0], toks, true)) == NULL)
    {
      bunny_perror("split");
      return (false);
    }
  if (split[0])
    {
      for (rd = 0; rd < NBRCELL(commands); ++rd)
	if (leftmatch(split[0], commands[rd].command))
	  {
	    ret = commands[rd].func(prog, &split[1]);
	    bunny_delete_split(split);
	    return (ret);
	  }
      printfall(prog, "Unrecognized command.\n");
    }
  bunny_delete_split(split);
  return (true);
}
