#ifndef		__XMLPARSE_C__
# define	__XMLPARSE_C__

# include	"XMLParser.h"
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h>
# include	<stdio.h>

/*
** Parse the asked file to create the tree in XML.
*/
message		*XMLparse(char *path)
{
  char		**tabToken;
  message	*msg;

  if (!(tabToken = XMLtoken_parse(path, XMLSEPARATOR, XMLTO_IGNORE, XMLTO_REMOVE)))
    return (NULL);
  msg = XMLcreate_tree(tabToken);
  delete_tab(tabToken);
  if (msg == NULL)
    return (NULL);
  msg->type = XML;
  msg->name = strdup(path);
  return (msg);
}

/*
** Create a flux handling message.
** Set g_file_flux and g_flux_id
** They can't be modifyed until closed.
** Once closed cannot be reopened.
*/
message		*XMLparseFlux(int *fd, int id)
{
  char		**tabToken;
  message	*msg;
  
  if (*fd >= 0)
    g_fd = *fd;
  else
    return (NULL);
  if (!(tabToken = XMLtoken_parse_flux(fd, JSONSEPARATOR, JSONTO_IGNORE, JSONTO_REMOVE)))
    return (NULL);
  if (!(msg = malloc(sizeof(*msg))))
    return (NULL);
  msg->id = id;
  msg->next = NULL;
  msg->prev = NULL;
  XMLfeed_tree(msg, tabToken, id, 1);
  if (msg == NULL)
    return (NULL);
  msg->type = XML;
  msg->name = NULL;
  g_flux_id = msg->id;
  return (msg);
}

/*
** 
*/
void		XMLfeedFlux(int *fd, message *msg, int id)
{
  char		**tabToken;
  char		**tmp;

  if (msg != NULL && (msg->type != JSON || msg->name != NULL))
    return ;
  if (!(tabToken = XMLtoken_parse_flux(fd, JSONSEPARATOR, JSONTO_IGNORE, JSONTO_REMOVE)))
    {
      g_fd = -1;
      return ;
    }
  if (msg == NULL)
    {
      msg = XMLparseFlux(fd, id);
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
  XMLfeed_tree(msg, g_file_flux, id, 0);
  return ;
}

/*
** Serialize the tree (message) in the given file (path) in XML format
** Creates the file if needed. Use XMLserializeMode to specify the opening flag.
*/
void            XMLserialize(const char *path, message *msg)
{
  int           fd;

  if (path == NULL)
    fd = 1;
  else
    {
      fd = creat(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IWOTH | S_IROTH);
      if (fd == -1) // Error while opening and/or creating file.
	return ;
      XMLwriting(fd, msg);
    }
}

/*
** Serialize the tree (message) in the given file (path) in XML format
** Creates the file if needed with given flags (flags)
*/
void            XMLserializeMode(const char *path, message *msg, int flags)
{
  int           fd;

  if (path == NULL)
    fd = 1;
  else
    {
      fd = open(path, flags);
      if (fd == -1) // Error while opening and/or creating file.
        return ;
      XMLwriting(fd, msg);
    }
}

#endif		/* __XMLPARSE_C__ */
