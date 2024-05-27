/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

int			ingame_test_command(int			argc,
					    const char * const	*argv,
					    const char		*cmd,
					    const char		*cmd_addr)
{
  const char		*toks[] = {" ", NULL};
  const char * const	*spt;
  bool			match;
  int			i;

  if ((spt = bunny_split(cmd, toks, true)) == NULL)
    {
      bunny_perror(cmd);
      return (-1);
    }
  if (spt[0] == NULL)
    {
      bunny_delete_split(spt);
      fprintf(stderr, "Script error: command %s is invalid.\n", cmd_addr);
      return (-1);
    }
  for (i = 0; spt[i] && i < argc; ++i)
    if (strcasecmp(argv[i], spt[i]))
      break ; 
  match = spt[i] == NULL;
  bunny_delete_split(spt);
  return (match ? 1 : 0);
}
