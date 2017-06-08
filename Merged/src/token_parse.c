#ifndef		__TOKEN_PARSE_C__
# define	__TOKEN_PARSE_C__

# include	"string_utils.h"
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h>

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

/*
** Separates 'string' and cut it at 'pos' bytes.
** Return a string allocated.
*/
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

/*
** Read the whole file and retrun it in a char *
*/
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

/*
** Counts how much space is needed to stock the file in separated token.
** Return the number of separator counted added with none separators string also counted.
*/
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

/*
** Retrun the first separator string encountered in 'file'.
** If the begining of the 'file' isn't a separator, all the data throught the next token is returned.
** Takes count of quote.
** Ex : data = "="
** data is a basic string, the first '=' is a token/separator and "=" is considerated as a basic string
*/
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

/*
** Basically a strcmp between segment and ign.
** Should segment be ignored ? If every bytes of 'segment' are in sep, it should be.
** Else it shouldn't.
*/
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

/*
** Add an element ('elem') in 'ret'. 'elem' is cleaned before being added in 'ret'
*/
char		**add_element(char **ret, char *elem, const char *to_remove)
{
  int		i;

  i = 0;
  while (ret[i] != NULL)
    i++;
  ret[i] = clean(elem, to_remove);
  return (ret);
}

/*
** Do all the dirty job by calling upper functions.
*/
char		**token_parse(char *path, char *sep, const char *to_ignore, const char *to_remove)
{
  char		**ret;
  char		*segment;
  char		*file;
  size_t	file_size;
  
  // Open and read the file.
  if (!(file = read_file(path, &file_size)))
    return (NULL);
  // Allocat 'ret' to full it with every token and basic string.
  file_size = count_element(file, sep) + 2;
  if (!(ret = calloc(file_size, sizeof(*ret))))
    return (NULL);
  // As long as it receive a string, stock it in 'ret'
  while ((segment = return_token_string(file, "\",{}[]:")) != NULL)
    {
      if (ignore_it(segment, to_ignore) == -1)
	ret = add_element(ret, segment, to_remove);
      free(segment);
    }
  free(file);
  return (ret);
}

/*
** free everything in a char **
*/
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

#endif		/* __TOKEN_PARSE_C__ */
