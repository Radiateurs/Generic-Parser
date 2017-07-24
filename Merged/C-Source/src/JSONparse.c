#ifndef		__JSONPARSE_C__
# define	__JSONPARSE_C__

# include	"JSONParser.h"
# include	"string_utils.h"
# include	<stdio.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h>
# include	<unistd.h>

/*
** Parse and create a tree from the given file (path).
*/
message		*JSONparse(char *path)
{
  char		**tabToken;
  message	*msg;

  if (!(tabToken = token_parse(path, JSONSEPARATOR, JSONTO_IGNORE, JSONTO_REMOVE))) // Cut all the file in token
    return (NULL);
  msg = JSONcreate_tree(tabToken);
  delete_tab(tabToken);
  if (msg == NULL)
    return (NULL);
  msg->type = JSON;
  msg->name = strdup(path);
  return (msg);
}

/*
** Create a flux handling message.
** Set g_file_flux and g_flux_id
** They can't be modifyed until closed.
** Once closed cannot be reopened.
*/
message		*JSONparseFlux(int *fd, int id)
{
  char		**tabToken;
  message	*msg;
  
  if (*fd >= 0)
    g_fd = *fd;
  else
    return (NULL);
  if (!(tabToken = token_parse_flux(fd, JSONSEPARATOR, JSONTO_IGNORE, JSONTO_REMOVE)))
    return (NULL);
  if (!(msg = malloc(sizeof(*msg))))
    return (NULL);
  msg->id = id;
  msg->next = NULL;
  msg->prev = NULL;
  JSONfeed_tree(msg, tabToken, id, 1);
  if (msg == NULL)
    return (NULL);
  msg->type = JSON;
  msg->name = NULL;
  g_flux_id = msg->id;
  return (msg);
}

/*
** 
*/
void		JSONfeedFlux(int *fd, message *msg, int id)
{
  char		**tabToken;
  char		**tmp;

  if (msg != NULL && (msg->type != JSON || msg->name != NULL))
    return ;
  if (!(tabToken = token_parse_flux(fd, JSONSEPARATOR, JSONTO_IGNORE, JSONTO_REMOVE)))
    {
      g_fd = -1;
      return ;
    }
  if (msg == NULL)
    {
      msg = JSONparseFlux(fd, id);
      return ;
    }
  if (!(tmp = mtab_concat(g_file_flux, tabToken)))
    {
      free(g_file_flux);
      free(tabToken);
      return ;
    }
  free(g_file_flux);
  free(tabToken);
  g_file_flux = tmp;
  JSONfeed_tree(msg, g_file_flux, id, 0);
  return ;
}

/*
** Serialize the tree (message) in the given file (path) in JSON format
** Creates the file if needed. Use JSONserializeMode to specify the opening flag.
*/
void		JSONserialize(const char *path, message *msg)
{
  int		fd;

  if (path == NULL)
    fd = 1;
  else
    {
      fd = creat(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IWOTH | S_IROTH);
      if (fd == -1) // Error while opening and/or creating file.
	return ;
      JSONwriting(fd, msg);
    }
}

/*
** Serialize the tree (message) in the given file (path) in JSON format
** Creates the file if needed. Use JSONserializeMode to specify the opening flag.
*/
void		JSONserializeMode(const char *path, message *msg, int flags)
{
  int		fd;

  if (path == NULL)
    fd = 1;
  else
    {
      fd = open(path, flags);
      if (fd == -1) // Error while opening and/or creating file.
	return ;
      JSONwriting(fd, msg);
    }
}

#endif		/* __JSONPARSE_C__ */
