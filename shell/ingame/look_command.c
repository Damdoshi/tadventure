/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"shell.h"

bool			shell_ingame_look_command(t_program		*prog,
						  const char * const	*params)
{
  t_bunny_configuration	*room;
  const char		*str;
  const char		*tmp;
  bool			back;

  back = false;
  if ((room = ingame_get_room(prog, NULL)) == NULL)
    return (false);

  if (bunny_configuration_getf(room, &str, "Background[0]"))
    {
      t_brightness	bn = BUNCHANGE;

      if (bunny_configuration_getf(room, &tmp, "Background[1]"))
	bn = strcasecmp("bright", tmp) == 0 ? BBRIGHT : BNORMAL;
      if (shell_textd(prog, CUNCHANGE, BUNCHANGE, FUNCHANGE,
		      shell_color(str, true), bn, FUNCHANGE) == false)
	return (false);
      back = true;
    }
	      
  if (params == NULL || (params[0] != NULL && params[1] == NULL))
    {
      bool		fline = false;

      if (back)
	printfall(prog, "%*s", prog->term_size.x + 1, "\n");
      if (bunny_configuration_getf(room, &str, "Name"))
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

      if (bunny_configuration_getf(room, &str, "Picture"))
	{
	  if (shell_display_picture(prog, str) == false)
	    return (false);
	  printfall(prog, "\n");
	}
      if (bunny_configuration_getf(room, NULL, "Description"))
	{
	  printfall(prog, "/");
	  for (int i = 0; bunny_configuration_getf(room, &str, "Description[%d]", i); ++i)
	    printfall(prog, "%s", temp_trim(str));
	  printfall(prog, "\n\n\n");
	}
    }
  else
    {
      // Regarder un objet
    }
  temp_trim(NULL);
  shell_text_default(prog, true, true);
  return (true);
}
