/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		<signal.h>
#include		<termios.h>
#include		"shell.h"

bool			shell_menu(t_program		*prog);
bool			shell_ingame(t_program		*prog);

int			shell_mode(t_program		*prog)
{
  static bool		(*const func[KLAST])(t_program	*prog) = {
    [KMENU] = shell_menu,
    [KINGAME] = shell_ingame
  };
  struct termios	termios;
  __sighandler_t	hdl;
  int			ret;

  // On laisse les appels systemes gérer
  hdl = signal(SIGPIPE, SIG_IGN);  
  tcgetattr(0, &termios);
  // On fait des trucs
  tcsetattr(0, TCSANOW, &termios);

  shell_text_default(prog, true, true);
  
  shell_menu_title_screen(prog);
  
  if (shell_menu_help_command(prog, NULL) == false)
    return (false);
  do
    {
      ret = EXIT_FAILURE;
      if (shell_get_terminal_size(prog) == false)
	break ;
      else if (func[prog->klondike](prog) == false)
	break ;
      ret = EXIT_SUCCESS;
    }
  while (prog->klondike < KLAST);

  tcsetattr(0, TCSANOW, &termios);
  signal(SIGPIPE, hdl);
  return (ret);
}

