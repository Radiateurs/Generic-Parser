#include	<string_utils.h>

int		strcis(const char *str, char c)
{
  int		i = 0;

  while (str[i] != '\0')
    {
      if (str[i] == c)
	return (i);
      i++;
    }
  return (-1);
}

char		*clean(const char *src, const char *to_ignore)
{
  int		i = 0;
  int		lenght = 0;
  char		*dest;

  while (src[i] != '\0')
    {
      if (strcis(to_ignore, src[i]) == -1)
	lenght++;
      i++;
    }
  if (!(dest = malloc(sizeof(*dest) * (lenght + 1))))
    return (NULL);
  i = 0;
  lenght = 0;
  while (src[i] != '\0')
    {
      if (strcis(to_ignore, src[i]) == -1)
	{
	  dest[lenght] = src[i];
	  lenght++;
	}
      i++;
    }
  dest[lenght] = '\0';
  return (dest);
}

char		*mconcat(char *saved, char *buff)
{
  char		*dest;
  int		i = 0;
  int		size = 0;

  size = ((saved != NULL) ? strlen(saved) : 0) + ((buff != NULL) ? strlen(buff) : 0) + 1;
  if (!(dest = malloc(sizeof(*dest) * size)))
    return (NULL);
  size = 0;
  while (saved != NULL && saved[i] != '\0')
    {
      dest[i] = saved[i];
      i++;
    }
  while (buff != NULL && buff[size] != '\0')
    {
      dest[i + size] = buff[size];
      size++;
    }
  dest[i + size] = '\0';
  return (dest);
}

int		str_is_num(const char *str)
{
  int		i = 0;

  while (str[i] != '\0')
    {
      if (str[i] < '0' && str[i] > '9')
	return (-1);
      i++;
    }
  return (0);
}

int		str_n_is_num(const char *str, int max)
{
  int		i = 0;

  while (str[i] != '\0' && i < max)
    {
      if (str[i] < '0' && str[i] > '9')
	return (-1);
      i++;
    }
  return (0);
}

int		is_a_token(const char *fragment, const char *sep)
{
  int		i = 0;

  while (fragment[i] != '\0')
    {
      if (strcis(sep, fragment[i]) == -1)
	return (-1);
      i++;
    }
  return (0);
}
