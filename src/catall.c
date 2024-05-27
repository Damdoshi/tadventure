/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	"shell.h"

static char	*bstrlcat(char			*target,
			  size_t		tlen,
			  const char		*src)
{
  size_t	i;
  size_t	j;

  i = 0;
  j = 0;
  while (target[i] && i < tlen)
    i = i + 1;
  while (src[j] && i < tlen - 1)
    {
      target[i] = src[j];
      i = i + 1;
      j = j + 1;
    }
  target[i] = 0;
  return (&target[i]);
}

bool		catall(t_program		*prog,
		       const char		*data,
		       size_t			len)
{
  const char	*toks = "=@~^%&";
  const char	*tmp;
  char		*target = &bunny_big_buffer[0];
  size_t	tlen = sizeof(bunny_big_buffer);
  size_t	i;

  i =  0;
  while (i < len)
    {
      if (prog->no_format)
	{
	  char buf[2] = {data[i], 0};
	  target = bstrlcat(target, tlen, buf);
	  i = i + 1;
	  continue ;
	}
	    
      if (data[i] == '\\')
	target = bstrlcat(target, tlen, "\n");
      else if (data[i] == '/')
	target = bstrlcat(target, tlen, "\t");
      else if (data[i] == '*')
	{
	  if (!prog->fat)
	    shell_textd(prog,
			CUNCHANGE, BUNCHANGE, FFAT,
			CUNCHANGE, BUNCHANGE, FUNCHANGE
			);
	  else
	    shell_textd(prog,
			CUNCHANGE, BUNCHANGE, FNORMAL,
			CUNCHANGE, BUNCHANGE, FUNCHANGE
			);
	  prog->fat = !prog->fat;
	}
      else if (data[i] == '#')
	{
	  if (!prog->bright)
	    shell_textd(prog,
			CUNCHANGE, BBRIGHT, FUNCHANGE,
			CUNCHANGE, BUNCHANGE, FUNCHANGE
			);
	  else
	    shell_textd(prog,
			CUNCHANGE, BNORMAL, FUNCHANGE,
			CUNCHANGE, BUNCHANGE, FUNCHANGE
			);
	  prog->bright = !prog->bright;
	}
      else if ((tmp = strchr(toks, data[i])) != NULL)
	{
	  if (!prog->color)
	    shell_textd(prog,
			CRED + ((size_t)tmp - (size_t)toks), BUNCHANGE, FUNCHANGE,
			CUNCHANGE, BUNCHANGE, FUNCHANGE
			);
	  else
	    shell_textd(prog,
			CWHITE, BUNCHANGE, FUNCHANGE,
			CUNCHANGE, BUNCHANGE, FUNCHANGE
			);
	  prog->color = !prog->color;
	}
      else if (data[i] != '\n')
	{
	  char buf[2] = {data[i], 0};
	  target = bstrlcat(target, tlen, buf);
	}
      else
	{
	  bstrlcat(target, tlen, "\n");
	  writeall(prog);
	  target = &bunny_big_buffer[0];
	}
      i = i + 1;
    }

  if (target - &bunny_big_buffer[0] > 1024 * 1024 * 4)
    return (writeall(prog));
  return (true);
}
