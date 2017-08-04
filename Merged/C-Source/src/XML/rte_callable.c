#ifndef		__RTE_CALLABLE_C__
# define	__RTE_CALLABLE_C__

# include	"generic_parser.h"

// Create a graph from the given file
double		nfXMLParseFile(char *path)
{
  ParserInit();
  if (!(g_msg = XMLparse(path)))
    return (-1);
  return (0);
}

// Open a message and create it from a flux
double		nfXMLParseFlux(int fd)
{
  message	*tmp;

  if (g_human_readable != 0 && g_human_readable != 1)
    ParserInit();
  if ((tmp = XMLparseFlux(&fd, getLastIDMessage(g_msg) + 1)) == NULL)
    return (-1);
  if (addMessage(&g_msg, tmp) == 0)
    return (-1); // Verify error code
  if (fd == -1)
    return (-1); // Verify error code
  return (0);
}

// Compete the flux message
double		nfXMLFeedFlux()
{
  if (g_fd == -1)
    return (-1); // verify error code
  XMLfeedFlux(&g_fd, g_msg, g_flux_id);
  if (g_fd == -1)
    return (-1); // Verify error code
  return (0);
}

// Serialize the message in XML structure
double		nfXMLSerialize(char *path)
{
  if (g_msg == NULL)
    return (-1);
  XMLserialize(path, g_msg);
  return (0);
}

// Serialize the message in XML and create the file with certains mode
double		nfXMLSerializeMode(char *path, int flags)
{
  if (g_msg == NULL)
    return (-1);
  XMLserializeMode(path, g_msg, flags);
  return (0);
}

#endif		/* __RTE_CALLABLE_C__ */
