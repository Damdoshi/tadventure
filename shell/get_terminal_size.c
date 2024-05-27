/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		<sys/ioctl.h>
#include		"shell.h"

bool			shell_get_terminal_size(t_program	*prog)
{
  static bool		first = false;
  struct winsize	wsiz;

  // Récupération de la taille du terminal
  if (ioctl(1, TIOCGWINSZ, &wsiz) != 0)
    {
      if (!first)
	perror("get_terminal_size");
      prog->term_size.x = 80;
      prog->term_size.y = 40;
      first = true;
      // return (false);
      return (true);
    }
  prog->term_size.x = wsiz.ws_col;
  prog->term_size.y = wsiz.ws_row;
  return (true);
}
