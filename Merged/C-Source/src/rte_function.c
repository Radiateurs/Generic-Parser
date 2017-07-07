#ifndef		__RTE_FUNCTION_C__
# define	__RTE_FUNCTION_C__

# include	"generic_parser.h"

double		nfSetHumanReadable(char *sep, int nb_spacer)
{
  setHumanReadable(sep[0], nb_spacer);
  return (0);
}

double		nfCleanMemory()
{
  if (g_msg == NULL)
    return (-1); // Verify error code
  deleteMessages(&g_msg);
  return (0);
}

#endif		/* __RTE_FUNCTION_C__ */
