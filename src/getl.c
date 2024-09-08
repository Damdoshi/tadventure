/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	"tadventure.h"

const char	*getl(t_program		*prog,
		      const char	*def,
		      const char	*pat,
		      ...)
{
  char		buffer[4096];
  va_list	lst;
  const char	*ret;

  va_start(lst, pat);
  snprintf(buffer, sizeof(buffer), "[].%s.%s", prog->language, pat);
  if (!bunny_configuration_vgetf(prog->configuration, &ret, buffer, lst))
    return (def);
  return (ret);
}
