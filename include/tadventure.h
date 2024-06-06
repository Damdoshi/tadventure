/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#ifndef				__TADVENTURE_H__
# define			__TADVENTURE_H__
# include			<lapin.h>

typedef enum			e_klondike
  {
    KMENU,
    KINGAME,
    KLAST
  }				t_klondike;

typedef enum			e_display
  {
    DDEFAULT			= -1,
    DGRAPHICS,
    DCURSES,
    DSHELL
  }				t_display;

extern const t_bunny_context	gl_contexts[KLAST];

typedef struct			s_program
{
  // Display mode
  t_bunny_window		*window;

  // Shell mode
  t_bunny_size			term_size;
  bool				fat;
  bool				bright;
  bool				color;
  bool				no_format;

  // Curses mode
  //

  // Software props
  const char			*configuration_files[128];
  size_t			configuration_files_nbr;
  const char			*language;
  t_bunny_configuration		*configuration;
  t_bunny_configuration		*parameters;
  t_display			display_mode;
  t_klondike			klondike;
  bool				game_changed;
  struct timeval		before;
  int				elapsed; // Real time. // Binded with conf
  bool				display_clock; // Binded

  // Game props
  char				*title; // Binded
  int				day; // Binded
  int				hour; // Binded
  int				minute; // Binded
  int				second; // Binded
}				t_program;

int				screen_mode(t_program		*prog);
int				curses_mode(t_program		*prog);
int				shell_mode(t_program		*prog);

int				leftmatch(const char		*str,
					  const char		*pattern);
int				rightmatch(const char		*str,
					   const char		*pattern);

bool				handle_parameters(int		argc,
						  char		**argv,
						  t_program	*prog);
bool				load_game(t_program		*prog);
int				help(void);

void				error(const char		*pattern,
				      ...)
  __attribute__ ((format (printf, 1, 2)));
bool				printfall(t_program		*program,
					  const char		*pattern,
					  ...)
  __attribute__ ((format (printf, 2, 3)))
  ;
bool				writeall(t_program		*program);
bool				catall(t_program		*prog,
				       const char		*data,
				       size_t			len);
int				trim(char			*str);
const char			*temp_trim(const char		*str);

typedef int			t_ingame_function(t_program	*prog,
						  int		argc,
						  const char * const *argv);
t_ingame_function
  ingame_handle_action
;

int				ingame_dont_know(t_program	*program,
						 const char	*action);
t_bunny_configuration		*ingame_get_room(t_program	*prog,
						 const char	*name);

bool				emergency_save(t_program	*prog);
bool				save(t_program			*prog,
				     const char			*name);

int				ingame_test_command(int		argc,
						    const char * const *argv,
						    const char	*cmd,
						    const char	*cmd_addr);
bool				ingame_try_execute_action(t_program *program,
							  t_bunny_configuration	*action,
							  int argc,
							  const char * const *argv);
int				ingame_time_pass(t_program	*program);

bool				rebind_variables(t_program	*prog);

bool				ingame_reword_command(t_program	*prog,
						      char	*cmd);

const char			*language(t_program		*prog,
					  const char		*str);
const char			*string(t_program		*prog,
					const char		*pattern,
					...);

int				randint(void);

#endif	/*			__TADVENTURE_H__		*/
