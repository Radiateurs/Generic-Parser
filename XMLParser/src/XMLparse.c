#include	"XMLParser.h"
#include	<stdio.h>

void		XMLparse(char *path)
{
  char		**tabToken;
  message	*msg;

  tabToken = token_parse(path);
  msg = create_tree(tabToken);
  if (msg != NULL)
    {
      dumpMessage(msg);
      deleteMessages(&msg);
    }
  delete_tab(tabToken);
  return ;
}
