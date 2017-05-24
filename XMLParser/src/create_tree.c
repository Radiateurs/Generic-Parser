#include	"XMLParser.h"
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
  info.current_tree_type = NONE;
  info.last_tree_type = NONE;
  info.is_in_list = 0;
  info.is_in_tab = 0;
  info.textChar = '#';
  info.attrChar = '@';
  return (info);
}

/*
** Look for multiple same-named lists
** Modify them to put them all in a tab.
*/

message		*xmlParseTab(message *msg)
{
  segment	*tmp;

  tmp = msg->segment;
  while (tmp->parent != NULL)
    tmp = tmp->parent;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp != NULL)
    {
      findAndModifyListInTab(&tmp);
      tmp = tmp->next;
    }
  return (msg);
}


/*
** Second main function.
** Create the tree once the file has been shred into tokens.
*/
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
	  dprintf(2, "SYNTAX ERROR\n");
	  deleteMessages(&ret);
	  return (NULL);
	}
      if (is_a_token(tokens[i], "<>/\"=\'") == 0)
	state_token_fragment(tokens[i], &info);
      if (is_a_token(tokens[i], "<>/\"=\'") != 0 ||			\
	  (info.last_state == DECLARATIONB && info.current_state != LISTE) || \
	  info.last_state == TYPETOKENB || info.current_state == ESNAME || info.current_state == VALUE)
	state_non_token_fragment(tokens, &info, &i);
      if (info.current_tree_type != NOPE)
	add_chunk_to_tree(&info, &ret);
      i++;
      info.last_state = info.current_state;
    }
  if (info.content != NULL)
    free(info.content);
  if (info.seg_name != NULL)
    free(info.seg_name);
  if (info.elem_name != NULL)
    free(info.elem_name);
  return (xmlParseTab(ret));
}
