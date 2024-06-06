/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"shell.h"

const char		*language(t_program		*prog,
				  const char		*str)
{
  const char		*tmp;

  if (prog->language == NULL)
    return (str);
  if (bunny_configuration_getf
      (prog->configuration, &tmp, "%s.%s", prog->language, str))
    return (tmp);
  return (str);
}

