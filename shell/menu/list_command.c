/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		<stdint.h>
#include		<limits.h>
#include		<sys/types.h>
#include		<dirent.h>
#include		"shell.h"

int			_shell_menu_list_command(t_program		*prog,
						 int			dry,
						 int			*longest)
{
  struct dirent		*dirent;
  DIR			*dir;
  unsigned int		cnt;
  int			col = prog->term_size.x;

  if (longest)
    col = col / (*longest + 2);
  cnt = 0;
  if ((dir = opendir("save/")) == NULL)
    goto Conclude;
  while ((dirent = readdir(dir)) != NULL)
    if (dirent->d_type != DT_REG)
      continue ;
    else if (rightmatch(dirent->d_name, ".dab"))
      {
	char		buffer[1024];
	int64_t		maxlen = strlen(dirent->d_name) - 4;
	int		len;

	len = snprintf(buffer, sizeof(buffer), "%0*u", dry, cnt);
	len += snprintf(&buffer[len], sizeof(buffer) - len, " - %-.*s", (int)maxlen, dirent->d_name);
	if (len >= (int)sizeof(buffer))
	  return (-1);
	if (dry == -1 && longest && *longest < len)
	  {
	    if (*longest < prog->term_size.x - 1)
	      *longest = len;
	    else
	      *longest = prog->term_size.x - 1;
	  }

	cnt += 1;

	if (dry != -1)
	  {
	    while (len < prog->term_size.x / col && len < (int)sizeof(buffer) - 1)
	      buffer[len++] = ' ';
	    buffer[len] = 0;
	    printfall(prog, "%.*s ", prog->term_size.x / col - 1, buffer);
	    if (cnt % col == 0)
	      printfall(prog, "\n");
	  }
      }
  closedir(dir);
  if (cnt % col != 0 && dry != -1)
    printfall(prog, "\n");
 Conclude:
  if (dry != -1)
    printfall(prog, "Amount of save file found: %u.\n", cnt);
  return (cnt);
}

bool			shell_menu_list_command(t_program		*prog,
						const char * const	*p)
{
  int			longest;
  int			nbr;
  int			i;

  (void)p;
  longest = -1;
  if ((nbr = _shell_menu_list_command(prog, -1, &longest)) == -1)
    return (false);
  for (i = 0; nbr > 0; ++i)
    nbr /= 10;
  return (_shell_menu_list_command(prog, i, &longest));
}

