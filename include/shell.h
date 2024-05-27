/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#ifndef			__SHELL_H__
# define		__SHELL_H__
# include		"tadventure.h"

typedef enum		e_shell_color
  {
    CUNCHANGE		= -1,
    CBLACK,
    CRED,
    CGREEN,
    CYELLOW,
    CBLUE,
    CMAGENTA,
    CCYAN,
    CWHITE,
  }			t_shell_color;

t_shell_color		shell_color(const char		*str,
				    bool		back);

typedef enum		e_brightness
  {
    BUNCHANGE		= -1,
    BNORMAL,
    BBRIGHT
  }			t_brightness;

typedef enum		e_fatness
  {
    FUNCHANGE		= -1,
    FNORMAL,
    FFAT
  }			t_fatness;

typedef struct		e_shell_text
{
  t_shell_color		color;
  t_brightness		brightness;
  t_fatness		fatness;
}			t_shell_text;

bool			shell_textd(t_program			*prog,
				    t_shell_color		fcol,
				    t_brightness		fbri,
				    t_fatness			ffat,
				    t_shell_color		bcol,
				    t_brightness		bbri,
				    t_fatness			bfat);
bool			shell_text(t_program			*prog,
				   t_shell_text			front,
				   t_shell_text			back);
bool			shell_text_swap(t_program		*prog);
bool			shell_text_default(t_program		*prog,
					   bool			front,
					   bool			back);

typedef bool		t_shell_menu_command(t_program		*prog,
					     const char * const	*params);
t_shell_menu_command
  shell_menu_play_command,
  shell_menu_load_command,
  shell_menu_list_command,
  shell_menu_help_command,
  shell_menu_exit_command,

  shell_ingame_menu_command,
  shell_ingame_save_command,
  shell_ingame_look_command,
  shell_ingame_inventory_command
  ;
  

bool			shell_prompt(t_program			*prog);
bool			shell_get_terminal_size(t_program	*prog);
  
bool			shell_separator(t_program		*prog,
					char			c);

int			shell_menu_title_screen(t_program	*prog);
bool			shell_display_picture(t_program		*prog,
					      const char	*file);

#endif	/*		__SHELL_H__			*/
