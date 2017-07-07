#ifndef		__JSON_CREATE_TREE_C__
# define	__JSON_CREATE_TREE_C__

# include	"JSONParser.h"
# include	<stdio.h>


JSONtree_parser	JSONinit_tree_parser()
{
  JSONtree_parser	info;

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

message		*JSONcreate_tree(char **tokens)
{
  message	*ret;
  int		i;
  JSONtree_parser	info;
  
  ret = NULL;
  info = JSONinit_tree_parser();
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
	JSONstate_token_fragment(tokens[i], &info, ret);
      if (is_a_token(tokens[i], ",[]{}:\"") != 0 || (info.current_state == VALUE || \
							  info.current_state == ESNAME))
	JSONstate_non_token_fragment(tokens, &info, &i, ret);
      if (info.current_tree_type != NOPE)
	JSONadd_chunk_to_tree(&info, &ret);
      i++;
      info.last_state = info.current_state;
    }
  return (ret);
}

#endif		/* __JSON_CREATE_TREE_C__ */
