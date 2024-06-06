/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

bool			handle_parameters(int		argc,
					  char		**argv,
					  t_program	*prog)
{
  int			cnt = 1;

  if (argc == 0 || *argv == NULL)
    return (true);
  if (argv[0][0] != '-')
    {
      if (prog->configuration_files_nbr >= NBRCELL(prog->configuration_files))
	{
	  error("Too many game files. Maximum is %d.\n", NBRCELL(prog->configuration_files));
	  return (help());
	}
      prog->configuration_files[prog->configuration_files_nbr++] = argv[0];
    }
  else if (leftmatch(argv[0], "--display="))
    {
      if (leftmatch(&argv[0][10], "graphics")) // -g
	prog->display_mode = DGRAPHICS;
      else if (leftmatch(&argv[0][10], "curses")) // -c
	prog->display_mode = DCURSES;
      else if (leftmatch(&argv[0][10], "shell")) // -s
	prog->display_mode = DSHELL;
      else if (leftmatch(&argv[0][10], "default")) // -s
	prog->display_mode = -1;
      else
	{
	  error("Unsupported display mode '%s'.\n", &argv[0][10]);
	  return (help());
	}
    }

  return (handle_parameters(argc - cnt, &argv[cnt], prog));
}
