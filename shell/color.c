/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"shell.h"

t_shell_color		shell_color(const char		*str,
				    bool		back)
{
  const char		*c[] = {
    "black",
    "red",
    "green",
    "yellow",
    "blue",
    "magenta",
    "cyan",
    "white"
  };

  for (size_t i = 0; i < NBRCELL(c); ++i)
    if (strcasecmp(c[i], str) == 0)
      return (i);
  if (back)
    return (0);
  return (NBRCELL(c) - 1);
}

