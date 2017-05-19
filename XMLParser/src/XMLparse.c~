#include	"XMLParser.h"
#include	<stdio.h>

void		XMLparse(char *path)
{
  char		**tabToken;
  message	*msg;
  int		i = 0;

  tabToken = token_parse(path);
  while (tabToken[i] != NULL)
    {
      puts(tabToken[i]);
      i++;
    }
  msg = create_tree(tabToken);
  if (msg != NULL)
    {
      dumpMessage(msg);
      deleteMessages(&msg);
    }
  delete_tab(tabToken);
  return ;
}
