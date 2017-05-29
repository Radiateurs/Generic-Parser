#include	"JSONParser.h"
#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>


void		JSONinit()
{
  g_human_readable = 0;
  g_nb_tab = 0;
}

/*
** Parse and create a tree from the given file (path).
*/
message		*JSONparse(char *path)
{
  char		**tabToken;
  message	*msg;

  if (!(tabToken = token_parse(path))) // Cut all the file in token
    return (NULL);
  msg = create_tree(tabToken);
  delete_tab(tabToken);
  return (msg);
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
