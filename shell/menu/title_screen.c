/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	<signal.h>
#include	<termios.h>
#include	"shell.h"

int		shell_menu_title_screen(t_program	*prog)
{
  const char	*str;

  if (shell_get_terminal_size(prog) == false)
    return (-1);
  if (!bunny_configuration_getf(prog->configuration, &str, "GeneralProperties.TitleScreen"))
    printfall(prog, "Welcome in %s.\n", prog->title);
  else if (shell_display_picture(prog, str) == false)
    return (-1);
  return (0);
}
