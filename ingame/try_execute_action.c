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
  bool		done = true;
  bool		result;

  result = true;
  
  bunny_clear_configuration(program->parameters);
  done = done && bunny_configuration_setf(program->parameters, argc, "[0]");
  if (argc == 0)
    done = done && bunny_configuration_setf(program->parameters, "", "[1][0]");
  else
    for (int i = 0; done && i < argc; ++i)
      done = done && bunny_configuration_setf(program->parameters, argv[i], "[1][%d]", i);
  if (done == false)
    {
      error("Script error: Cannot write parameters for %s.\n", bunny_configuration_get_address(action));
      return (false);
    }  
  
  if (bunny_configuration_getf(action, NULL, "Condition"))
    if (bunny_configuration_executef(action, &result, false, program->parameters, "Condition") == false)
      {
	error("Script error: invalid function %s.Condition.\n", bunny_configuration_get_address(action));
	return (false);
      }
  
  if (result)
    {
      if (bunny_configuration_getf(action, NULL, "Passed"))
	if (!bunny_configuration_executef(action, NULL, false, program->parameters, "Passed"))
	  error("Script error: invalid function %s.Passed.\n", bunny_configuration_get_address(action));
    }
  else
    {
      if (bunny_configuration_getf(action, NULL, "Failed"))
	if (!bunny_configuration_executef(action, NULL, false, program->parameters, "Failed"))
	  error("Script error: invalid function %s.Failed.\n", bunny_configuration_get_address(action));
    }
  return (true);
}
