#ifndef		__RTE_CALLABLE_C__
# define	__RTE_CALLABLE_C__

# include	"generic_parser.h"

double		nfXMLParseFile(char *path)
{
  ParserInit();
  if (!(g_msg = XMLparse(path)))
    return (-1);
  return (0);
}

double		nfXMLSerialize(char *path)
{
  if (g_msg == NULL)
    return (-1);
  XMLserialize(path, g_msg);
  return (0);
}

double		nfXMLSerializeMode(char *path, int flags)
{
  if (g_msg == NULL)
    return (-1);
  XMLserializeMode(path, g_msg, flags);
  return (0);
}

#endif		/* __RTE_CALLABLE_C__ */
