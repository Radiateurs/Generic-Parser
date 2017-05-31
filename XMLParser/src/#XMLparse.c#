#include	"XMLParser.h"
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>

void		XMLinit()
{
  g_human_readable = 0;
  g_nb_tab = 1;
}

message		*XMLparse(char *path)
{
  char		**tabToken;
  message	*msg;

  tabToken = token_parse(path);
  msg = create_tree(tabToken);
  delete_tab(tabToken);
  if (msg != NULL)
    return (msg);
  return (NULL);
}

/*
** Serialize the tree (message) in the given file (path) in JSON format
** Creates the file if needed. Use JSONserializeMode to specify the opening flag.
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
** Serialize the tree (message) in the given file (path) in JSON format
** Creates the file if needed. Use JSONserializeMode to specify the opening flag.
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

