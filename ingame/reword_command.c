/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

bool			ingame_reword_command(t_program		*prog,
					      char		*cmd)
{
  const char		*toks[] = {" ", "\t", "\r", "\v", "\n", NULL};
  char			*nw;
  char			**forge;
  const char * const	*tmp;
  bool			fnd;
  int			len;
  int			nlen;
  int			j;
  int			i;

  nlen = 0;
  if ((tmp = bunny_split(cmd, toks, true)) == NULL)
    {
      bunny_perror("reword");
      return (false);
    }
  for (len = 0; tmp[len]; ++len);
  forge = bunny_alloca((len + 1) * sizeof(*forge));
  for (j = 0; j < len; ++j)
    {
      const char	*ext;
      
      for (i = 0; (fnd = bunny_configuration_getf
		   (prog->configuration, &ext, "GeneralProperties.RemovedWord[%d]", i));
	   ++i)
	if (strcasecmp(ext, tmp[j]) == 0)
	  break ;
      if (!fnd)
	forge[nlen++] = (char*)tmp[j];
    }
  forge[nlen] = NULL;
  nw = bunny_stick((const char * const *)forge, " ", true);
  bunny_delete_split(tmp);
  if (nw == NULL)
    {
      bunny_perror("stick");
      bunny_freea(forge);
      return (false);
    }
  strcpy(cmd, nw);
  bunny_free(nw);
  bunny_freea(forge);
  return (true);
}

