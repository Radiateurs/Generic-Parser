#ifndef		__JSON_CREATE_TREE_C__
# define	__JSON_CREATE_TREE_C__

# include	"JSONParser.h"
# include	<stdio.h>

/*
** Init variable in the JSONtree_parser struture
*/
JSONtree_parser	JSONinit_tree_parser()
{
  JSONtree_parser	info;

  info.seg_name = NULL; // Needed for the name of a segment
  info.elem_name = NULL; // needed for the name of an element
  info.attr_name = NULL; // needed for the name of an attribut
  info.content = NULL; // needed for the value of a content
  info.current_state = NONE; // needed for the current state during parsing.
  info.last_state = NONE; // needed for the lastest state during parsing.
  info.current_tree_type = NOPE; // needed for the current tree state during parsing. If during the parsing the graph is in a List, an array or anything else
  info.last_tree_type = NOPE; // needed for the lastest tree state during parsing. If during the parsing the graph was in a List, an array or anything else
  info.is_in_list = 0; // needed to know if during the process of parsing, the graph has been through a list.
  info.is_in_tab = 0; // needed to know if during the process of parsing, the graph has been through a tab.
  info.list_in_tab = 0;  // used as a boolean, needed to know if the graph has been through a tab and a list.
  return (info);
}

void		JSONfeed_tree(message *msg, char **tokens, int msg_id, int reset)
{
  static int	i = 0;
  static JSONtree_parser	info;
  message	*pointed_msg;

  // If reset is == 1 or more reset static variable. Else won't touch it.
  if (reset)
    {
      i = 0;
      info = JSONinit_tree_parser();
    }
  // Move to the correct msg
  pointed_msg = msg;
  while (msg != NULL && msg->prev != NULL && msg->id != (unsigned int)msg_id)
    msg = msg->prev;
  while (msg != NULL && msg->next != NULL && msg->id != (unsigned int)msg_id)
    msg = msg->next;
  // if not found get back to the given msg. If it's wrong it's the user problem.
  if (msg != NULL && msg->id != (unsigned int)msg_id)
    msg = pointed_msg;
  // Go to the deepest position to get back at the last pos.
  while (msg != NULL && msg->segment != NULL && msg->segment->next != NULL)
    msg->segment = msg->segment->next;
  while (msg != NULL && msg->segment != NULL && msg->segment->child != NULL)
    msg->segment = msg->segment->child;
  while (msg != NULL && msg->segment != NULL && msg->segment->next != NULL)
    msg->segment = msg->segment->next;
  while (msg != NULL && msg->segment != NULL && msg->segment->element != NULL && msg->segment->element->next != NULL)
    msg->segment->element = msg->segment->element->next;
  i = 0;
  // start to parse and convert in graph.
  while (tokens[i] != NULL)
    {
      if (info.current_state == ERROR)
	{
	  dprintf(2, "SYNTAX ERROR\tNear : \"%s %s %s\"\nCurrent tree parsed : \n", \
		  tokens[i - 1], tokens[i], tokens[i + 1]);
	  if (msg != NULL)
	    dumpMessage(msg);
	  return ;
	}
      if (is_a_token(tokens[i], ",[]{}:\"") == 0)
	JSONstate_token_fragment(tokens[i], &info, msg);
      if (is_a_token(tokens[i], ",[]{}:\"") != 0 || (info.current_state == VALUE || \
							  info.current_state == ESNAME))
	JSONstate_non_token_fragment(tokens, &info, &i, msg);
      if (info.current_tree_type != NOPE)
	JSONadd_chunk_to_tree(&info, &msg);
      i++;
      info.last_state = info.current_state;
    }
  return ;
}

/*
** Create the graph (tree) from tokens.
*/
message		*JSONcreate_tree(char **tokens)
{
  message	*ret;
  int		i;
  JSONtree_parser	info;
  
  ret = NULL;
  info = JSONinit_tree_parser();
  newMessage(&ret, getLastIDMessage(g_msg));
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
