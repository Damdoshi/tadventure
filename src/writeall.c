/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

/*
** C'est un poil le désordre. Plusieurs virages conceptuels
** ont été fait en cours de route et j'ai un peu la flemme pour l'instant
** de reconstruire.
*/

#include	<errno.h>
#include	<unistd.h>
#include	"tadventure.h"

static bool	_writeall(t_program		*prog,
			  const char		*data,
			  size_t		len)
{
  size_t	i;

  (void)prog;
  i = 0;
  while (i < len)
    {
      ssize_t	tmp;
      
      if ((tmp = write(1, &data[i], len - i)) == -1)
	{
	  if (errno != EAGAIN)
	    return (false);
	  tmp = 0;
	}
      i += tmp;
    }
  return (true);
}

// Servira a écrire dans un buffer si on est en mode graphique.
// Sera associé a un reset


bool		writeall(t_program		*program)
{
  bool		wt = _writeall(program, bunny_big_buffer, strlen(bunny_big_buffer));

  bunny_big_buffer[0] = 0;
  return (wt);
}
