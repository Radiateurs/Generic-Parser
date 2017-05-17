#include	"JSONParser.h"
#include	<stdio.h>

void		JSONparse(char *path)
{
  char		**tabToken;
  message	*msg;

  if (!(tabToken = token_parse(path)))
    return ;
  msg = create_tree(tabToken);
  if (msg != NULL)
    {
      dumpMessage(msg);
      deleteMessages(&msg);
    }
  delete_tab(tabToken);
  return ;
}

/*
** To do once the JSON parse is done and functionnal
*/
/* void		JSONserialize(char *path, message *msg) */
/* { */
/*   int		fd; */

/*   if (path == NULL) */
/*     fd = 1; */
/*   else */
/*     { */
      
/*     } */
/* } */
