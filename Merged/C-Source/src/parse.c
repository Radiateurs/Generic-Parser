#ifndef		__PARSE_C__
# define	__PARSE_C__

# include	"generic_parser.h"

/*
** Init the global variables
*/
void		ParserInit()
{
  g_nb_spacer = 0;
  g_human_readable = 0;
  g_spacer = '\t';
  g_attribut = '@';
  g_text = '#';
}

/*
** Call it once to set on human readable mode.
** tab is here to specifies the number of tabulations to put into dependencies
*/
void		setHumanReadable(char spacer, int nb)
{
  if (nb == 0)
    {
      g_human_readable = 0;
      return ;
    }
  if (nb != 0)
    g_nb_spacer = nb;
  if (spacer != '\t' && spacer != ' ')
    return ;
  else
    g_spacer = spacer;
  g_human_readable = 1;
}

#endif		/* __PARSE_C__ */
