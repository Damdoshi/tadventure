/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include		"tadventure.h"

t_bunny_response	screen_menu_key(t_bunny_event_state	state,
					t_bunny_keysym		sym,
					t_program		*prog)
{
  if (state == GO_DOWN)
    return (GO_ON);
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  (void)prog;
  return (GO_ON);
}

