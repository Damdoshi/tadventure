/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	<stdio.h>
#include	"shell.h"

bool		shell_separator(t_program		*prog,
				char			c)
{
  int		i;

  shell_textd(prog, CBLACK, BBRIGHT, FFAT, CUNCHANGE, BUNCHANGE, FUNCHANGE);
  for (i = 0; i < prog->term_size.x; ++i)
    printfall(prog, "%c", c);
  shell_text_default(prog, true, true);
  printfall(prog, "\n");
  return (true);
}
