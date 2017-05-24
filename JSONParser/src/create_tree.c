#include	"JSONParser.h"
#include	<stdio.h>


tree_parser	init_tree_parser()
{
  tree_parser	info;

  info.seg_name = NULL;
  info.elem_name = NULL;
  info.attr_name = NULL;
  info.content = NULL;
  info.current_state = NONE;
  info.last_state = NONE;
  info.current_tree_type = NOPE;
  info.last_tree_type = NOPE;
  info.is_in_list = 0;
  info.is_in_tab = 0;
  info.list_in_tab = 0;
  return (info);
}

message		*create_tree(char **tokens)
{
  message	*ret;
  int		i;
  tree_parser	info;
  
  ret = NULL;
  info = init_tree_parser();
  newMessage(&ret, 1);
  i = 0;
  while (tokens[i] != NULL)
    {
      if (info.current_state == ERROR)
	{
	  dprintf(2, "SYNTAX ERROR\tNear : \"%s %s %s\"\nCurrent tree parsed : \n", \
		  tokens[i - 1], tokens[i], tokens[i + 1]);
	  if (ret != NULL)
	    dumpMessage(ret);
	  deleteMessages(&ret);
	  return (NULL);
	}
      if (is_a_token(tokens[i], ",[]{}:\"") == 0)
	state_token_fragment(tokens[i], &info, ret);
      if (is_a_token(tokens[i], ",[]{}:\"") != 0 || (info.current_state == VALUE || \
							  info.current_state == ESNAME))
	state_non_token_fragment(tokens, &info, &i, ret);
      if (info.current_tree_type != NOPE)
	add_chunk_to_tree(&info, &ret);
      i++;
      info.last_state = info.current_state;
    }
  return (ret);
}
