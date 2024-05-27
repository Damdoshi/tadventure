/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	"tadventure.h"

bool		ingame_try_execute_action(t_program		*program,
					  t_bunny_configuration	*action,
					  int			argc,
					  const char * const	*argv)
{
  bool		result;

  (void)program;
  // Temporaire
  (void)argc;
  (void)argv;

  result = true;
  bunny_clear_configuration(program->parameters);
  if (bunny_configuration_getf(action, NULL, "Condition"))
    {
      if (bunny_configuration_executef(action, false, program->parameters, "Condition") == false)
	{
	  fprintf(stderr, "Script error: invalid function %s.Condition (1).\n", bunny_configuration_get_address(action));
	  return (false);
	}
      if (!bunny_configuration_getf(action, &result, "Condition"))
	{
	  fprintf(stderr, "Script error: invalid function  %s.Condition (2).\n", bunny_configuration_get_address(action));
	  return (false);
	}
    }
  if (result)
    {
      if (!bunny_configuration_getf(action, NULL, "Passed"))
	return (true);
      if (!bunny_configuration_executef(action, false, program->parameters, "Passed"))
	fprintf(stderr, "Script error: invalid function %s.Passed.\n", bunny_configuration_get_address(action));
      return (true);
    }
  if (!bunny_configuration_getf(action, NULL, "Failed"))
    return (true);
  if (!bunny_configuration_executef(action, false, NULL, "Failed"))
    fprintf(stderr, "Script error: invalid function %s.Failed.\n", bunny_configuration_get_address(action));
  return (true);
}
