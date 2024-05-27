/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	<unistd.h>
#include	"tadventure.h"
#include	"shell.h"

bool		shell_prompt(t_program		*prog)
{
  const char	*prompt = "[>] ";
  int		i;

  if (shell_separator(prog, '_') == false)
    return (false);
  shell_textd(prog, CWHITE, BBRIGHT, FFAT, CBLACK, BNORMAL, FFAT);
  for (i = 0; i < prog->term_size.x; ++i)
    printfall(prog, " ");
  printfall(prog, "\r");
  bunny_configuration_getf(prog->configuration, &prompt, "[].CurrentCharacter->Prompt");
  if (printfall(prog, "%s", prompt) == false)
    return (false);
  writeall(prog);
  shell_text_default(prog, true, true);
  return (true);
}
