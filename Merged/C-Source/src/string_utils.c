#ifndef		__STRING_UTILS_C__
# define	__STRING_UTILS_C__

# include	<string_utils.h>

/*
** Verify if 'c' is in 'str'
** Return the position of 'c' in 'str' if it's in it
** Return -1 if 'c' isn't in 'str'
*/
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

/*
** Earase every char in 'to_ignore' that are in 'src'
** Return a new allocated char *
*/
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

/*
** Acts like strcat but allocates a new string and concatatains the two strings ('saved' and 'buff').
*/
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

/*
** Verify if the whole string 'str' contains number.
** Retrun 0 if so
** Return -1 if not
*/
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

/*
** Acts like str_is_num but it will check 'max' bytes.
** If 'max' is upper than the lenght of 'str' it will check the whole string
** Return the exact same things as str_is_num
*/
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

/*
** Verify if the 'fragment' string contains only 'sep' char.
** The order isn't checked. As long that every bytes of 'fragment' are contained in sep it's okay.
** Return -1 if not.
** Retrun 0 if so.
*/
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

#endif		/* __STRING_UTILS_C__ */
