/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		<ctype.h>
#include		"shell.h"

bool			shell_ingame_menu_command(t_program		*prog,
						  const char * const	*params)
{
  (void)params;
  if (prog->game_changed)
    {
      char		buffer[64] = {0};
      ssize_t		len;

      do
	{
	  if (printfall(prog, "%s", getl(prog, "Save before leaving (Y|n)? ", "SaveBeforeLeaving")) == false)
	    return (emergency_save(prog));
	  writeall(prog);
	  if ((len = read(0, buffer, sizeof(buffer))) == -1)
	    return (emergency_save(prog));
	  buffer[0] = tolower(buffer[0]);
	  if (buffer[0] == '\n' || buffer[0] == '\r' || buffer[0] == prog->yes)
	    {
	      do
		{
		  printfall(prog, "%s: ", getl(prog, "Please enter a name (empty for lastsave): ", "PleaseEnterSaveName"));
		  writeall(prog);
		  if ((len = read(0, buffer, sizeof(buffer) - 1)) == -1)
		    return (emergency_save(prog));
		  buffer[len] = 0;
		  trim(buffer);
		  if (!buffer[0])
		    strcpy(buffer, "lastsave");
		  if (save(prog, buffer))
		    break;
		}
	      while (1);
	      break ;
	    }
	  else if (buffer[0] == prog->no)
	    break ;
	}
      while (1);
    }
  prog->klondike = KMENU;
  shell_menu_help_command(prog, NULL);
  return (true);
}

