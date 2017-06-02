#include	"string_utils.h"
#include	"generic_parser.h"
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>

int		XMLfirst_token_pos(const char *buff, const char *sep)
{
  int		i = 0;
  int		slash = 0;

  while (buff[i] != '\0')
    {
      if (slash == 1)
	{
	  i = (buff[i] == '\0') ? i : i + 1;
	  continue ;
	}
      if (buff[i] == '\\')
	slash = 1;
      if (strcis(sep, buff[i]) > -1)
	return (i);
      i++;
    }
  return (-1);
}

char		*XMLreturn_token_string(const char *file, const char *sep)
{
  static unsigned int	i = 0;
  int		pos;
  char		*to_ret;

  if (file[i] == '\0')
    return (NULL);
  if ((pos = XMLfirst_token_pos(file + i, sep)) == -1)
    {
      pos = i;
      while (file[i] != '\0')
	i++;
      return (strdup(file + pos));
    }
  if (pos == 0)
    {
      to_ret = strndup(file + i, 1);
      i++;
      return (to_ret);
    }
  to_ret = strndup(file + i, pos);
  i += pos;
  return (to_ret);
}

char		**XMLtoken_parse(char *path, const char *separator, const char *to_ignore, const char *to_remove)
{
  char		**ret;
  char		*segment;
  char		*file;
  size_t	file_size;

  file = read_file(path, &file_size);
  if (!(ret = calloc(count_element(file, separator) + 1, sizeof(*ret))))
    return (NULL);
  while ((segment = XMLreturn_token_string(file, separator)) != NULL)
    {
      if (ignore_it(segment, to_ignore) == -1)
	ret = add_element(ret, segment, to_remove);
      free(segment);
    }
  free(file);
  return (ret);
}
