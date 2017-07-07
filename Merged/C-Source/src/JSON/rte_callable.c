#ifndef		__RTE_CALLABLE_C__
# define	__RTE_CALLABLE_C__

# include	"generic_parser.h"

double		nfJSONParseFile(char *path)
{
  ParserInit();
  if ((g_msg = JSONparse(path)) == NULL)
    return (-1);
  return (0);
}

double		nfJSONSerialize(char *path)
{
  if (g_msg == NULL)
    return (-1);
  JSONserialize(path, g_msg);
  return (0);
}

double		nfJSONSerializeMode(char *path, int flags)
{
  if (g_msg == NULL)
    return (-1);
  JSONserializeMode(path, g_msg, flags);
  return (0);
}

#endif		/* __RTE_CALLABLE_C__ */
