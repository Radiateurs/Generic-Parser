#ifndef		__RTE_CALLABLE_C__
# define	__RTE_CALLABLE_C__

# include	"generic_parser.h"
# include	"JSONParser.h"

/*
** Called by RTE.
** Create a graph from a file.
*/
double		nfJSONParseFile(char *path)
{
  message	*tmp;

  if (g_human_readable != 0 && g_human_readable != 1)
    ParserInit();
  if ((tmp = JSONparse(path)) == NULL)
    return (-1);
  addMessage(&g_msg, tmp);
  return (0);
}

/*
** Called by RTE.
** Create a graph from a flux.
*/
double		nfJSONParseFlux(int fd)
{
  message	*tmp;

  if (g_human_readable != 0 && g_human_readable != 1)
    ParserInit();
  if ((tmp = JSONparseFlux(&fd, getLastIDMessage(g_msg) + 1)) == NULL)
    return (-1);
  if (addMessage(&g_msg, tmp) == 0)
    return (-1); // Verify error code
  if (fd == -1)
    return (-1); // Verify error code
  return (0);
}

/*
** Called by RTE.
** Complete a graph from a flux.
*/
double		nfJSONFeedFlux()
{
  if (g_fd == -1)
    return (-1); // verify error code
  JSONfeedFlux(&g_fd, g_msg, g_flux_id);
  if (g_fd == -1)
    return (-1); // Verify error code
  return (0);
}

/*
** Called by RTE.
** Serialize any graph in JSON.
*/
double		nfJSONSerialize(char *path)
{
  if (g_msg == NULL)
    return (-1);
  JSONserialize(path, g_msg);
  return (0);
}

/*
** Called by RTE.
** Serialize any graph in JSON in a specialized creation mode.
*/
double		nfJSONSerializeMode(char *path, int flags)
{
  if (g_msg == NULL)
    return (-1);
  JSONserializeMode(path, g_msg, flags);
  return (0);
}

#endif		/* __RTE_CALLABLE_C__ */
