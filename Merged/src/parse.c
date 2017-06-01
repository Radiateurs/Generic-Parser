#include	"generic_parser.h"

void		ParserInit()
{
  g_nb_spacer = 0;
  g_human_readable = 0;
  g_spacer = '\t';
}

void		setHumanReadable(char spacer, int nb)	// tab is here to specifies the number of
							// tabulations to put into dependencies
							// Call it once to set on human readable mode.
{
  if (nb != 0)
    g_nb_spacer = nb;
  if (spacer != '\t' && spacer != ' ')
    return ;
  else
    g_spacer = spacer;
  g_human_readable = 1;
}

