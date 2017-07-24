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
