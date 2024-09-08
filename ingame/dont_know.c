/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

int			ingame_dont_know(t_program	*program,
					 const char	*action)
{
  const char		*str;
  int			nbr;

  nbr = bunny_configuration_casesf
    (program->configuration, "[].CurrentCharacter->DontKnow");
  if (!bunny_configuration_getf
      (program->configuration, &str,
       "CurrentCharacter->DontKnow[%d]", rand() % nbr)
      )
    {
      printfall(program, "?\n");
      return (0);
    }
  int		spec = 0;
      
  for (nbr = 0; str[nbr]; ++nbr)
    if (str[nbr] == '%')
      {
	if (str[nbr + 1] != 's')
	  {
	    error("Script error: Invalid token in '%s'. Only a single %%s is supported.\n", str);
	    return (-1);
	  }
	if ((spec += 1) > 1)
	  {
	    error("Script error: Too many string token in '%s'.\n", str);
	    return (-1);
	  }
      }
  printfall(program, str, action);
  printfall(program, "\n");
  return (0);
}
