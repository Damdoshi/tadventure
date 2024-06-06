/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

bool			rebind_variables(t_program		*prog)
{
  t_bunny_configuration	*gp;

  if (!bunny_configuration_getf(prog->configuration, &gp, "GeneralProperties"))
    {
      error("Script error: GeneralProperties missing.\n");
      return (false);
    }

  bunny_configuration_bindf(gp, &prog->elapsed, "Elapsed");
  bunny_configuration_bindf(gp, &prog->display_clock, "DisplayClock");
  
  if (!bunny_configuration_bindf(gp, &prog->title, "Title"))
    {
      error("Script error: Game title missing.\n");
      return (false);
    }

  bunny_configuration_bindf(gp, &prog->day, "Day");
  bunny_configuration_bindf(gp, &prog->hour, "Hour");
  bunny_configuration_bindf(gp, &prog->minute, "Minute");
  bunny_configuration_bindf(gp, &prog->second, "Second");

  prog->language = NULL;
  bunny_configuration_getf(prog->configuration, &prog->language, "GeneralProperties.Language");
  
  return (true);
}
