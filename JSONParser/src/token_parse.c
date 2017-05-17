#include	<string.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>

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

int		first_token_pos(const char *buff, const char *sep, int quote)
{
  int		i = 0;

  if (quote == 1)
    {
      while (buff[i] != '\0' && buff[i] != '\"')
	i++;
      return ((buff[i] == '\0') ? -1 : i);
    }
  while (buff[i] != '\0')
    {
      if (strcis(sep, buff[i]) > -1)
	return (i);
      i++;
    }
  return (-1);
}

char		*trunc_string(char *string, int pos)
{
  char		*ret;
  int		i = 0;

  if (!(ret = malloc(sizeof(*ret) * (pos + 1))))
    return (NULL);
  while (string[i] != '\0' && i < pos)
    {
      ret[i] = string[i];
      i++;
    }
  ret[i]= '\0';
  return (ret);
}

char		*read_file(char *path, size_t *file_size)
{
  struct stat	sstat;
  int		fd;
  char		*file;

  if (stat(path, &sstat) == -1)
    return (NULL);
  *file_size = sstat.st_size;
  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  if (!(file = malloc(sizeof(*file) * (*file_size + 1))))
    return (NULL);
  if (read(fd, file, *file_size) == -1)
    return (NULL);
  file[*file_size] = '\0';
  return (file);
}

unsigned int	count_element(char *file, const char *sep)
{
  int		i, j;
  unsigned int	token;
  int		quote;
  
  token = 0;
  i = 0;
  quote = 0;
  while (file[i] != '\0')
    {
      if ((j = first_token_pos(file + i, sep, quote)) == -1)
	return (token);
      if (file[i + j] == '\"')
	quote = (quote == 1) ? 0 : 1;
      if (j > 0)
	{
	  i += j;
	  token += 2;
	}
      else
	token++;
      i++;
    }
  return (token);
}

char		*return_token_string(const char *file, const char *sep)
{
  static unsigned int	i = 0;
  int		pos;
  char		*to_ret;
  static int	quote = 0;

  if (file[i] == '\0')
    return (NULL);
  if ((pos = first_token_pos(file + i, sep, quote)) == -1)
    {
      pos = i;
      while (file[i] != '\0')
	i++;
      return (strdup(file + pos));
    }
  if (pos == 0)
    {
      if (file[i] == '\"')
	quote = (quote == 1) ? 0 : 1;
      to_ret = strndup(file + i, 1);
      i++;
      return (to_ret);
    }
  to_ret = strndup(file + i, pos);
  i += pos;
  return (to_ret);
}

int		ignore_it(char *segment, const char *ign)
{
  int		i;

  i = 0;
  while (segment[i] != '\0')
    {
      if (strcis(ign, segment[i]) == -1)
	return (-1);
      i++;
    }
  return (0);
}

char		**add_element(char **ret, char *elem)
{
  int		i;

  i = 0;
  while (ret[i] != NULL)
    i++;
  ret[i] = clean(elem,"\t\r\n");
  return (ret);
}

char		**token_parse(char *path)
{
  char		**ret;
  char		*segment;
  char		*file;
  size_t	file_size;
  
  if (!(file = read_file(path, &file_size)))
    return (NULL);
  if (!(ret = calloc(count_element(file, "\",{}[]:") + 1, sizeof(*ret))))
    return (NULL);
  while ((segment = return_token_string(file, "\",{}[]:")) != NULL)
    {
      if (ignore_it(segment, " \t\r\n") == -1)
	ret = add_element(ret, segment);
      free(segment);
    }
  free(file);
  return (ret);
}

void		delete_tab(char **ptr)
{
  int		i = 0;

  if (ptr == NULL)
    return ;
  while (ptr[i] != NULL)
    {
      free(ptr[i]);
      i++;
    }
  free(ptr);
  ptr = NULL;
  return ;
}
