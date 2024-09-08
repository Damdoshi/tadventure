/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"shell.h"

static bool		_look(t_program					*prog,
			      t_bunny_configuration			*main_node)
{
  const char		*str;
  const char		*tmp;
  bool			back;
  bool			fline;

  back = fline = false;
  if (bunny_configuration_getf(main_node, &str, "Background[0]"))
    {
      t_brightness	bn = BUNCHANGE;

      if (bunny_configuration_getf(main_node, &tmp, "Background[1]"))
	bn = strcasecmp("bright", tmp) == 0 ? BBRIGHT : BNORMAL;
      if (shell_textd(prog, CUNCHANGE, BUNCHANGE, FUNCHANGE,
		      shell_color(str, true), bn, FUNCHANGE) == false)
	return (false);
      if (back)
	printfall(prog, "%*s", prog->term_size.x + 1, "\n");
    }

  if (bunny_configuration_getf(main_node, &str, "Name"))
    {
      printfall(prog, "  %-*s", (int)ceil(prog->term_size.x / 2) - 2, str);
      fline = true;
    }
  else
    printfall(prog, "%-*s", (int)ceil(prog->term_size.x / 2), "");
  
  if (prog->display_clock)
    {
      char		dbuffer[128];

      snprintf(dbuffer, sizeof(dbuffer), "#*%s %d %d:%d - %s*#",
	       language(prog, "Day"), prog->day, prog->hour, prog->minute,
	       string(prog, "CurrentCharacter->Name")
	       );
      printfall(prog, "%*s  ", (int)floor(prog->term_size.x / 2) - 2, &dbuffer[0]);
      fline = true;
    }
  else
    printfall(prog, "%*s", (int)floor(prog->term_size.x / 2), "");

  if (fline)
    printfall(prog, "\n\n");

  if (bunny_configuration_getf(main_node, &str, "Picture"))
    {
      if (shell_display_picture(prog, str) == false)
	return (false);
      printfall(prog, "\n");
    }

  if (bunny_configuration_getf(main_node, NULL, "Description"))
    {
      printfall(prog, "/");
      if (bunny_configuration_getf(main_node, &str, "Description"))
	printfall(prog, "%s", temp_trim(str));
      else
	for (int i = 0; bunny_configuration_getf(main_node, &str, "Description[%d]", i); ++i)
	  printfall(prog, "%s", temp_trim(str));
      printfall(prog, "\n\n\n");
    }

  temp_trim(NULL);
  shell_text_default(prog, true, true);
  return (true);
}

bool			shell_ingame_look_command(t_program		*prog,
						  const char * const	*params)
{
  t_bunny_configuration	*room;
  t_bunny_configuration	*it;
  const char		*str;
  int			desc;

  desc = 0;
  
  if ((room = ingame_get_room(prog, NULL)) == NULL)
    return (false);

  if (params == NULL || params[0] == NULL || (params[0] != NULL && params[1] == NULL))
    {
      if (_look(prog, room) == false)
	return (false);
      return (true);
    }
  for (size_t i = 1; params[i] != NULL; ++i)
    {
      for (bunny_configuration_all_childrenf(room, it, "Actions"))
	{
	  if (!bunny_configuration_getf(it, &str, "Target"))
	    continue ;
	  if (!bunny_configuration_getf(it, NULL, "Description"))
	    continue ;
	  if (strcasecmp(str, params[i]) != 0)
	    continue ;
	  if (_look(prog, it) == false)
	    return (false);
	  desc += 1;
	}
      for (bunny_configuration_all_childrenf(prog->configuration, it, "CurrentCharacter->Inventory"))
	{
	  const char *name;
	  t_bunny_configuration	*item;

	  if (!bunny_configuration_getf(it, &name, "."))
	    continue ;
	  if (!bunny_configuration_getf(prog->configuration, &item, "Items.%s", name))
	    continue ;
	  if (!bunny_configuration_getf(item, NULL, "Description"))
	    continue ;
	  if (_look(prog, item) == false)
	    return (false);
	  desc += 1;
	}
    }

  if (desc == 0)
    {
      str = getl
	(prog, "I don't see what I'm supposed to see",
	 "IDontSee[%zu]",
	 rand() % bunny_configuration_casesf
	 (prog->configuration, "[].%s.IDontSee", prog->language)
	 );
      printfall(prog, "%s.\n", str);
    }
  return (true);
}

