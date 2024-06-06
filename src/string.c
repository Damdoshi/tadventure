/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"shell.h"

const char		*string(t_program	*prog,
				const char	*pattern,
				...)
{
  const char		*str;
  va_list		lst;

  va_start(lst, pattern);
  if (!bunny_configuration_vgetf(prog->configuration, &str, pattern, lst))
    return ("");
  return (str);
}
