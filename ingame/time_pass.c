/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		<sys/time.h>
#include		"tadventure.h"

int			ingame_time_pass(t_program		*program)
{
  struct timeval	now;
  int			elapsed;

  gettimeofday(&now, NULL);
  program->elapsed += (elapsed = now.tv_sec - program->before.tv_sec);
  program->before = now;
  bunny_clear_configuration(program->parameters);
  if (!bunny_configuration_setf(program->parameters, elapsed, "[0]"))
    {
      error("Unexpected error: Cannot etastablish function call for time.\n");
      return (-1);
    }
  bunny_configuration_executef
    (program->configuration, NULL, false, program->parameters, "CurrentCharacter->Room->TimePass");
  return (0);
}

