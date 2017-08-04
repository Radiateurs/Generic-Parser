#ifndef		__RTE_FUNCTION_C__
# define	__RTE_FUNCTION_C__

# include	"generic_parser.h"

/*
** Set the output mode to "Human Readable"
*/
double		nfSetHumanReadable(char *sep, int nb_spacer)
{
  setHumanReadable(sep[0], nb_spacer);
  return (0);
}

/*
** Clean every global allocated variable
*/
double		nfCleanMemory()
{
  int		i;

  i = 0;
  while (g_file_flux != NULL && g_file_flux[i] != NULL)
    {
      free(g_file_flux[i]);
      i++;
    }
  if (g_msg == NULL)
    return (0); // Verify error code
  deleteMessages(&g_msg);
  return (0);
}

#endif		/* __RTE_FUNCTION_C__ */
