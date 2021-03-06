#ifndef		__XML_CREATE_TREE_C__
# define	__XML_CREATE_TREE_C__

# include	"XMLParser.h"
# include	<stdio.h>

// Init the XMLtree_parser structure's variable.
XMLtree_parser	XMLinit_tree_parser()
{
  XMLtree_parser	info;

  info.seg_name = NULL;
  info.elem_name = NULL;
  info.content = NULL;
  info.current_state = NONE;
  info.last_state = NONE;
  info.current_tree_type = NONE;
  info.last_tree_type = NONE;
  info.is_in_list = 0;
  info.is_in_tab = 0;
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
      XMLfindAndModifyListInTab(&tmp);
      tmp = tmp->next;
    }
  return (msg);
}

// Compte the graph from a flux
void		XMLfeed_tree(message *msg, char **tokens, int msg_id, int reset)
{
  static int	i = 0;
  static XMLtree_parser	info;
  message	*pointed_msg;

  // If reset is == 1 or more reset static variable. Else won't touch it.
  if (reset)
    {
      i = 0;
      info = XMLinit_tree_parser();
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
  // Analyze token by token
  while (tokens[i] != NULL)
    {
      // Must work on that
      if (info.current_state == ERROR)
	{
	  dprintf(2, "SYNTAX ERROR\nAt %s %s %s", tokens[i - 1], tokens[i], tokens[i + 1]);
	  if (msg != NULL)
	    dumpMessage(msg);
	  return ;
	}
      // verify is the pointed token is actually a token and not a string (data or name)
      if (is_a_token(tokens[i], "<>/\"=\'") == 0)
	XMLstate_token_fragment(tokens[i], &info);
      // if not a token
      if (is_a_token(tokens[i], "<>/\"=\'") != 0 ||			\
	  (info.last_state == DECLARATIONB && info.current_state != LISTE) || \
	  info.last_state == TYPETOKENB || info.current_state == ESNAME || info.current_state == VALUE)
	XMLstate_non_token_fragment(tokens, &info, &i);
      // once something has been found add the harvested data 
      if (info.current_tree_type != NOPE)
	XMLadd_chunk_to_tree(&info, &msg);
      i++;
      info.last_state = info.current_state;
    }
  // free / clean the used info.
  if (info.content != NULL)
    free(info.content);
  if (info.seg_name != NULL)
    free(info.seg_name);
  if (info.elem_name != NULL)
    free(info.elem_name);
  msg = xmlParseTab(msg);
  return ;
}

/*
** Second main function.
** Create the tree once the file has been shred into tokens.
*/
message		*XMLcreate_tree(char **tokens)
{
  message	*ret;
  int		i;
  XMLtree_parser	info;
  
  ret = NULL;
  info = XMLinit_tree_parser();
  newMessage(&ret, 1);
  i = 0;
  // Analyze token by token
  while (tokens[i] != NULL)
    {
      // Must work on that
      if (info.current_state == ERROR)
	{
	  dprintf(2, "SYNTAX ERROR\nAt %s %s %s", tokens[i - 1], tokens[i], tokens[i + 1]);
	  deleteMessages(&ret);
	  return (NULL);
	}
      // verify is the pointed token is actually a token and not a string (data or name)
      if (is_a_token(tokens[i], "<>/\"=\'") == 0)
	XMLstate_token_fragment(tokens[i], &info);
      // if not a token
      if (is_a_token(tokens[i], "<>/\"=\'") != 0 ||			\
	  (info.last_state == DECLARATIONB && info.current_state != LISTE) || \
	  info.last_state == TYPETOKENB || info.current_state == ESNAME || info.current_state == VALUE)
	XMLstate_non_token_fragment(tokens, &info, &i);
      // once something has been found add the harvested data 
      if (info.current_tree_type != NOPE)
	XMLadd_chunk_to_tree(&info, &ret);
      i++;
      info.last_state = info.current_state;
    }
  // free / clean the used info.
  if (info.content != NULL)
    free(info.content);
  if (info.seg_name != NULL)
    free(info.seg_name);
  if (info.elem_name != NULL)
    free(info.elem_name);
  return (xmlParseTab(ret));
}

#endif		/* __XML_CREATE_TREE_C__ */
