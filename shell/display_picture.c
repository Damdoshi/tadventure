/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	"shell.h"

static bool	_shell_display_picture(t_program	*prog,
				       const char	*file,
				       char		*pic)
{
  int		w;
  int		len;
  int		padding;
  int		i;
  double	j;

  for (w = 0; pic[w] && pic[w] != '\n'; ++w);
  if (pic[w] != '\n')
    {
      error("Script error: Invalid picture format in %s.\n", file);
      return (false);
    }
  w += 1;
  if ((len = strlen(pic)) % w != 0)
    {
      error("Script error: Irregular picture format in %s.\n", file);
      return (false);
    }
  if (w < prog->term_size.x)
    padding = (prog->term_size.x - w) / 2;
  else
    padding = 0;

  prog->no_format = true;

  for (i = 0; i < len / w; ++i)
    {
      for (j = 0; j < padding; ++j)
	printfall(prog, " ");
      if (padding)
	for (j = 0; j < w; ++j)
	  printfall(prog, "%c", pic[(int)j + i * w]);
      else
	{
	  for (j = 0; j < prog->term_size.x; j += 1)
	    {
	      char c = pic[(int)((j / prog->term_size.x) * w) + i * w];

	      if (c != '\n')
		printfall(prog, "%c", c);
	    }
	  printfall(prog, "\n");
	}
    }

  prog->no_format = false;
  return (true);
}

bool		shell_display_picture(t_program		*prog,
				      const char	*file)
{
  void		*pic;
	  
  if (bunny_load_file(file, &pic, NULL) == -1)
    {
      perror(file);
      return (false);
    }
  if (_shell_display_picture(prog, file, pic) == false)
    return (false);
  bunny_delete_file(pic, file);
  return (true);
}
