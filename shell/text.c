/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
**
** TAdventure
*/

#include	"shell.h"

static t_shell_text gl_texts[2] = {
  {CWHITE, BBRIGHT, FNORMAL},
  {CBLACK, BNORMAL, FNORMAL}
};

static void	set_gl(t_shell_text			*txt,
		       t_shell_color			c,
		       t_brightness			b,
		       t_fatness			f)
{
  if (c != CUNCHANGE)
    txt->color = c;
  if (b != BUNCHANGE)
    txt->brightness = b;
  if (f != FUNCHANGE)
    txt->fatness = f;
}

bool		shell_textd(t_program			*prog,
			    t_shell_color		fcol,
			    t_brightness		fbri,
			    t_fatness			ffat,
			    t_shell_color		bcol,
			    t_brightness		bbri,
			    t_fatness			bfat)
{
  char		buffer[16];
  int		len;
  int		backc;

  set_gl(&gl_texts[0], fcol, fbri, ffat);
  set_gl(&gl_texts[1], bcol, bbri, bfat);
  if (gl_texts[1].color == CBLACK && gl_texts[1].brightness == BNORMAL)
    backc = 9; // "Default color"
  else
    backc = gl_texts[1].color;
  len = snprintf(buffer, sizeof(buffer), "\e[%d;%d;%dm",
		 gl_texts[0].fatness,
		 gl_texts[0].color + 30 + (gl_texts[0].brightness ? 60 : 0),
		 backc + 40 + (gl_texts[1].brightness ? 60 : 0)
		 );
  return (catall(prog, buffer, len));
}

bool		shell_text(t_program		*prog,
			   t_shell_text		front,
			   t_shell_text		back)
{
  return (shell_textd
	  (prog,
	   front.color, front.brightness, front.fatness,
	   back.color, back.brightness, back.fatness)
	  );
}


bool		shell_text_default(t_program		*prog,
				   bool			front,
				   bool			back)
{
  if (front)
    {
      gl_texts[0].color = CWHITE;
      gl_texts[0].brightness = BNORMAL;
      gl_texts[0].fatness = FNORMAL;
    }
  if (back)
    {
      gl_texts[1].color = CBLACK;
      gl_texts[1].brightness = BNORMAL;
      gl_texts[1].fatness = FNORMAL;
    }
  return (shell_text(prog, gl_texts[0], gl_texts[1]));
}

bool		shell_text_swap(t_program		*prog)
{
  return (shell_text(prog, gl_texts[1], gl_texts[0]));
}

