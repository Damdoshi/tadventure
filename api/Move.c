/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

extern t_program	program;

// Cela pourrait être écrit en Dabsic.
// Mais je préfère que cela soit en C++
// afin de démontrer les aller-retours possible entre compilé et interprété
// et fournir une "lib standard" transcendante.
int			Move(const char		*character,
			     const char		*room)
{
  t_bunny_configuration	*rconf;
  t_bunny_configuration	*cconf;
  
  if (!bunny_configuration_getf(program.configuration, &rconf, "[].Rooms.%s", room))
    {
      error("Script error: Room %s does not exist.\n", room);
      return (0);
    }
  if (!bunny_configuration_getf(program.configuration, &cconf, "[].Characters.%s", character))
    {
      error("Script error: Character %s does not exist.\n", character);
      return (0);
    }
  bunny_configuration_setf(cconf, "", "Room");
  if (!bunny_configuration_getf(cconf, &cconf, "Room"))
    {
      error("Unexpected error: Cannot create room node for character %s.\n", character);
      return (0);
    }
  return (bunny_configuration_target(cconf,  rconf));
}

