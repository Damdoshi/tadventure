/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

bunny_declare_context(screen_menu);
bunny_declare_context(screen_ingame);

const t_bunny_context		gl_contexts[NBRCELL(gl_contexts)] = {
  [KMENU] = {
    .key = screen_menu_key,
    .loop = screen_menu_loop,
    .display = screen_menu_display
  },
  [KINGAME] = {
    .key = screen_ingame_key,
    .loop = screen_ingame_loop,
    .display = screen_ingame_display
  }
};

int			screen_mode(t_program		*program)
{
  const char		*title = "TAdventure";
  t_bunny_position	wsize = {1920, 1080};
  bool			fullscreen = true;

  if (bunny_position_configuration("", &wsize, program->configuration) == BD_ERROR)
    {
      error("Invalid resolution.\n");
      return (EXIT_FAILURE);
    }
  bunny_configuration_getf(program->configuration, &fullscreen, "Graphics.FullScreen");
  if (!(program->window = bunny_start(wsize.x, wsize.y, fullscreen, title)))
    {
      bunny_perror("Cannot open window");
      return (EXIT_FAILURE);
    }

  do
    {
      bunny_set_context(&gl_contexts[program->klondike]);
      bunny_loop(program->window, 50, program);
    }
  while (program->klondike < KLAST);
  bunny_stop(program->window);
  return (EXIT_SUCCESS);
}
