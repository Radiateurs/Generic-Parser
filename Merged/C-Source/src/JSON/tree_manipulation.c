#ifndef		__JSON_TREE_MANIPULATION_C__
# define	__JSON_TREE_MANIPULATION_C__

# include	"JSONParser.h"

/*
** Identify every type of the conent of an element.
*/
void		JSONidentify_token_type(const char *fragment, JSONtree_parser *info)
{
  int		decimal_pos;

  if (fragment[0] == '\"')
    {
      (*info).value_type = STRING;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  if (strcmp(fragment, "null") == 0)
    {
      (*info).value_type = NULLOBJ;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  if (strcmp(fragment, "true") == 0 || strcmp(fragment, "false") == 0)
    {
      (*info).value_type = BOOL;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  if ((decimal_pos = strcis(fragment, '.')) != -1 && str_n_is_num(fragment, decimal_pos) == 0 \
      && str_is_num(fragment + decimal_pos) == 0)
    {
      (*info).value_type = DECIMAL;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  if (str_is_num(fragment) == 0)
    {
      (*info).value_type = INTEGER;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  (*info).value_type = UNKNOW;
  return ;
}

/*
** Functions that allow to add a segment in the graph depending on the info variable.
*/
void		JSONadd_segment(JSONtree_parser *info, message **msg)
{
  int		is_a_group;
  int		seg_type;

  seg_type = ((*info).current_tree_type == SEGMENT) ? SSEG : ((*info).current_tree_type == LIST) ? SLIST : STAB;
  is_a_group = ((*info).current_tree_type == SEGMENT) ? 0 : 1;
  newSegment(&((*msg)->segment), (*info).elem_name, getNextID((*msg)->segment),	\
	     is_a_group, (*info).is_in_list + (*info).is_in_tab, (*info).is_in_list + (*info).is_in_tab, \
	     seg_type);
  if ((*info).elem_name != NULL)
    free((*info).elem_name);
  (*info).elem_name = NULL;
  (*info).last_tree_type = (*info).current_tree_type;
  (*info).current_tree_type = NOPE;
  if (seg_type == SLIST)
    (*info).is_in_list++;
  if (seg_type == STAB)
    (*info).is_in_tab++;
}

/*
** Once a tree_state has been set, the flow goes to this function
** This function help to add chunks of information and modify them to feet the graph.
*/
void		JSONadd_chunk_to_tree(JSONtree_parser *info, message **msg)
{
  switch ((*info).current_tree_type)
    {
    case CLOSEGROUP: // CLOSING A GROUP
      closeGroupSegment(&((*msg)->segment));
      if ((*info).last_state == TABE || ((*msg)->segment != NULL && (*msg)->segment->type == STAB))
      	(*info).is_in_tab--;
      if ((*info).last_state == LISTE ||((*msg)->segment != NULL && (*msg)->segment->type == SLIST))
      	(*info).is_in_list--;
      (*info).last_tree_type = (*info).current_tree_type;
      (*info).current_tree_type = NOPE;
      break;
    case SEGMENT: // ADD SEGMENT
      JSONadd_segment(info, msg);
      break;
    case LIST: // ADD LIST
      JSONadd_segment(info, msg);
      break;
    case TAB: // ADD TAB
      JSONadd_segment(info, msg);
      break;
    case ELEMENT: // ADD AN ELEMENT
      newElement(&((*msg)->segment->element), (*info).elem_name, getNextID((*msg)->segment), "", 10);
      if ((*info).elem_name != NULL)
	free((*info).elem_name);
      (*info).last_tree_type = (*info).current_tree_type;
      (*info).current_tree_type = NOPE;
      break;
    case ATTRIBUT: // ADD AN ATTRIBUT (the value of an element)
      if ((*info).content == NULL)
	return ;
      if (newElement(&((*msg)->segment->element), (*info).elem_name,	\
		     getNextID((*msg)->segment), (*info).content, (*info).value_type) == 0)
	{
	  (*info).current_state = ERROR;
	  return ;
	}
      if ((*info).attr_name != NULL)
	free((*info).attr_name);
      (*info).attr_name = NULL;
      if ((*info).elem_name != NULL)
	free((*info).elem_name);
      (*info).elem_name = NULL;
      if ((*info).content != NULL)
	free((*info).content);
      (*info).content = NULL;
      (*info).value_type = UNKNOW;
      (*info).current_tree_type = NOPE;
      (*info).last_tree_type = ATTRIBUT;
      break;
    default:
      break;
    }
}

#endif		/* __JSON_TREE_MANIPULATION_C__ */
