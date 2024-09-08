/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		<ctype.h>
#include		<signal.h>
#include		"tadventure.h"

t_program		program = {
  .display_mode = DDEFAULT,
  .title = "TAdventure Game",
  .klondike = KMENU,
  .term_size = {0, 0},
  .configuration_files_nbr = 0
};

void			crash_handler(int	sig)
{
  (void)sig;
  emergency_save(&program);
  exit(EXIT_FAILURE);
}

int			main(int		argc,
			     char		**argv)
{
  const char		*str;

  /*
  signal(SIGSEGV, crash_handler);
  signal(SIGPIPE, crash_handler);
  signal(SIGFPE, crash_handler);
  signal(SIGINT, SIG_IGN);
  */

  bunny_set_error_descriptor(2);
  bunny_set_log_filter("syntax");
  if ((program.parameters = bunny_new_configuration()) == NULL)
    {
      bunny_perror("new configuration for parameters");
      return (EXIT_FAILURE);
    }
  if (handle_parameters(argc + 1, &argv[1], &program) == false)
    return (EXIT_FAILURE);
  
  if (program.configuration_files_nbr == 0)
    {
      program.configuration_files[0] = "default.dab";
      program.configuration_files_nbr = 1;
    }
  if (load_game(&program) == false)
    return (EXIT_FAILURE);

  if (program.display_mode == DDEFAULT
      && bunny_configuration_getf(program.configuration, &str, "GeneralProperties.Display")
      && str[0] != 0)
    {
      if (strcasecmp(str, "shell") == 0)
	program.display_mode = DSHELL;
      else if (strcasecmp(str, "curses") == 0)
	program.display_mode = DCURSES;
      else if (strcasecmp(str, "graphics") == 0)
	program.display_mode = DGRAPHICS;
      else
	{
	  error("Script error: Unsupported display mode '%s'.\n", str);
	  return (help());
	}
    }
  else
    program.display_mode = DSHELL;

  program.yes = 'y';
  if (bunny_configuration_getf(program.configuration, &str, "%s.Y", program.language))
    program.yes = tolower(str[0]);
  program.no = 'n';
  if (bunny_configuration_getf(program.configuration, &str, "%s.N", program.language))
    program.no = tolower(str[0]);
  
  int		ret;

  if (program.display_mode == DGRAPHICS)
    ret = screen_mode(&program);
  else if (program.display_mode == DCURSES)
    ret = curses_mode(&program);
  else
    ret = shell_mode(&program);
  bunny_delete_configuration(program.configuration);
  return (ret);
}
