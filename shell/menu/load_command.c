/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		<sys/time.h>
#include		<ctype.h>
#include		<sys/stat.h>
#include		<sys/types.h>
#include		<dirent.h>
#include		"shell.h"

static int		retrieve_file(int				nbr,
				      char				*out,
				      size_t				max)
{
  struct dirent		*dirent;
  DIR			*dir;
  struct stat		st;
  uint64_t		best;

  best = 0;
  if ((dir = opendir("save/")) == NULL)
    return (0);
  while ((dirent = readdir(dir)) != NULL)
    if (dirent->d_type != DT_REG)
      continue ;
    else if (rightmatch(dirent->d_name, ".dab"))
      {
	if (nbr == -1)
	  {
	    char	tmp[max];
	    uint64_t	now;

	    snprintf(tmp, max, "save/%s", dirent->d_name);
	    if (stat(tmp, &st) != 0)
	      return (0);
	    // Vers des millisecondes
	    now = st.st_mtim.tv_sec * 1e3 + st.st_mtim.tv_nsec / 1e6;
	    if (now > best)
	      {
		// Le dernier qui écrit a gagné
		best = now;
		strcpy(out, tmp);
	      }
	  }
	else if (nbr-- <= 0)
	  {
	    snprintf(out, max, "save/%s", dirent->d_name);
	    return (1);
	  }
      }
  if (best > 0)
    return (1);
  return (0);
}

bool			shell_menu_load_command(t_program		*prog,
						const char * const	*p)
{
  char			buffer[1024];
  const char		*first = p[0];

  // On recharge la conf originale qu'on enrichira de la conf sauvegardée.
  // On cas ou, a terme, on ai une sauvegarde qui élimine les éléments
  // deja présent dans une référence (c'est pas le cas actuellement)
  bunny_delete_configuration(prog->configuration);
  prog->configuration = NULL;
  /*
  if (load_game(prog) == false)
    return (false);
  */
  if (first == NULL)
    {
      // Chargement du fichier le plus recent
      if (retrieve_file(-1, &buffer[0], sizeof(buffer)) == 0)
	{
	  printfall(prog, "No save file found.\n");
	  return (true);
	}
    }
  else
    {
      if (p[1] != NULL)
	{
	  printfall(prog, "Too many parameters.\n");
	  return (true);
	}
      if (isdigit(*first))
	{
	  // Chargement du fichier portant le numéro indiqué
	  int		ret = atoi(first);

	  if (retrieve_file(ret, &buffer[0], sizeof(buffer)) == 0)
	    {
	      printfall(prog, "Save file %d not found.\n", ret);
	      return (true);
	    }
	}
      else
	// Chargement du fihcier portant le nom indiqué
	snprintf(buffer, sizeof(buffer), "save/%s.dab", first);
    }

  printfall(prog, "Loading %s... ", buffer);
  if (!(prog->configuration = bunny_open_configuration(buffer, prog->configuration)))
    {
      bunny_perror("");
      return (true); // On ne quitte pas. C'est peut etre une erreur utilisateur.
    }
  rebind_variables(prog);
  printfall(prog, "Done\n");
  prog->klondike = KINGAME;
  gettimeofday(&prog->before, NULL);
  if (shell_ingame_look_command(prog, NULL) == false)
    return (false);
  return (true);
}
