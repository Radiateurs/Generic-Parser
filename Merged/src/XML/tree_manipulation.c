#include	"XMLParser.h"

void		XMLidentify_token_type(const char *fragment, XMLtree_parser *info)
{
  if (fragment[0] == '\"')
    {
      (*info).value_type = STRING;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  (*info).value_type = UNKNOW;
  return ;
}

void		XMLadd_segment(XMLtree_parser *info, message **msg)
{
  int		is_a_group;
  int		seg_type;

  is_a_group = ((*info).current_tree_type == SEGMENT) ? 0 : 1;
  seg_type = ((*info).current_tree_type == SEGMENT) ? SSEG : ((*info).current_tree_type == LIST) ? SLIST : STAB;
  newSegment(&((*msg)->segment), (*info).seg_name, getNextID((*msg)->segment),	\
	     is_a_group, 1, (*info).is_in_list + (*info).is_in_tab, \
	     seg_type);
  if ((*info).seg_name != NULL)
    free((*info).seg_name);
  (*info).seg_name = NULL;
  (*info).last_tree_type = (*info).current_tree_type;
  (*info).current_tree_type = NOPE;
  if (is_a_group)
    (*info).is_in_list++;
}

void		XMLadd_chunk_to_tree(XMLtree_parser *info, message **msg)
{
  char		*tmp;

  switch ((*info).current_tree_type)
    {
    case CLOSEGROUP:
      closeGroupSegment(&((*msg)->segment));
      if ((*info).last_tree_type == TAB)
	(*info).is_in_tab = 0;
      else
	(*info).is_in_list--;
      (*info).last_tree_type = (*info).current_tree_type;
      (*info).current_tree_type = NOPE;
      break;
    case SEGMENT:
      XMLadd_segment(info, msg);
      break;
    case LIST:
      XMLadd_segment(info, msg);
      break;
    case TAB:
      XMLadd_segment(info, msg);
      break;
    case ELEMENT:
      if ((*info).elem_name[0] != (*info).textChar)
	{
	  (*info).seg_name = malloc(sizeof(char) * 2);
	  (*info).seg_name[0] = (*info).attrChar;
	  (*info).seg_name[1] = '\0';
	  tmp = mconcat((*info).seg_name, (*info).elem_name);
	  free((*info).elem_name);
	  free((*info).seg_name);
	  (*info).elem_name = strdup(tmp);
	  free(tmp);
	  (*info).seg_name = NULL;
	}
      newElement(&((*msg)->segment->element), (*info).elem_name, getNextID((*msg)->segment));
      if ((*info).elem_name != NULL)
	free((*info).elem_name);
      (*info).elem_name = NULL;
      (*info).last_tree_type = (*info).current_tree_type;
      (*info).current_tree_type = NOPE;
      break;
    case ATTRIBUT:
      if ((*info).content == NULL)
	return ;
      if (((*msg)->segment != NULL && (*msg)->segment->element == NULL) || (*info).elem_name != NULL)
	if (newElement(&((*msg)->segment->element), (*info).elem_name,	\
		       getNextID((*msg)->segment)) != 1)
	  {
	    (*info).current_state = ERROR;
	    return ;
	  }
      newAttribut(&((*msg)->segment->element->attribut), (*info).attr_name, \
		  lastAttributID(((*msg)->segment->element->attribut)) + 1, (*info).content, (*info).value_type);
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
      if ((*info).last_tree_type != TAB)
	(*info).last_tree_type = ATTRIBUT;
      break;
    default:
      break;
    }
}

segment		*initNewParent(segment **old_parent, const char *childs_name)
{
  segment	*new_parent;
  
  if (!(new_parent = malloc(sizeof(*new_parent))))
    return (NULL);
  new_parent->name = strdup(childs_name);
  new_parent->is_a_group = 1;
  new_parent->type = STAB;
  new_parent->id = getNextID(*old_parent);
  new_parent->child = NULL;
  new_parent->element = NULL;
  new_parent->parent = (*old_parent)->parent;
  new_parent->next = NULL;
  new_parent->prev = NULL;
  new_parent->depth = (*old_parent)->depth;
  return (new_parent);
}

int		XMLmodifyListInTab(segment **old_parent, const char *childs_name)
{
  segment	*tmp;
  segment	*new_parent;
  int		for_ids;
  int	        on_off = 0;

  new_parent = initNewParent(old_parent, childs_name);
  while (*old_parent != NULL && (*old_parent)->prev != NULL)
    *old_parent = (*old_parent)->prev;
  while (on_off == 0)
    {
      if (*old_parent != NULL && *old_parent != new_parent && (*old_parent)->type == SLIST \
	  && (*old_parent)->name != NULL				\
	  && strcmp((*old_parent)->name, new_parent->name) == 0)
	{
	  (*old_parent)->depth++;
	  increaseChildDepth(old_parent);
	  free((*old_parent)->name);
	  (*old_parent)->name = NULL;
	  tmp = *old_parent;
	  removeIDSegment(old_parent, (*old_parent)->id);
	  tmp->id = getNextID(new_parent);
	  addChild(&new_parent, tmp);
	  while (*old_parent != NULL && (*old_parent)->prev != NULL)
	    *old_parent = (*old_parent)->prev;
	}
      else
	{
	  if (*old_parent == NULL || (*old_parent)->next == NULL)
	    on_off = 1;
	  else
	    *old_parent = (*old_parent)->next;
	}
    }
  addSegment(old_parent, new_parent, 0);
  for_ids = countSegment(*old_parent);
  while (*old_parent != NULL && (*old_parent)->next != NULL)
    *old_parent = (*old_parent)->next;
  while (*old_parent != NULL && (*old_parent)->prev != NULL)
    {
      (*old_parent)->id = for_ids;
      (*old_parent) = (*old_parent)->prev;
      for_ids--;
    }
  if (*old_parent != NULL)
    (*old_parent)->id = 1;
  return (0);
}

void		XMLfindAndModifyListInTab(segment **seg)
{
  segment	*tmp;

  if (seg == NULL || (*seg) == NULL)
    return ;
  while (*seg != NULL && (*seg)->prev != NULL)
    *seg = (*seg)->prev;
  while (*seg != NULL)
    {
      if ((*seg)->type != STAB)
	XMLfindAndModifyListInTab(&((*seg)->child));
      if ((*seg)->next == NULL)
	break;
      *seg = (*seg)->next;
    }
  while (*seg != NULL && (*seg)->prev != NULL)
    *seg = (*seg)->prev;
  tmp = *seg;
  while (tmp != NULL)
    {
      while (*seg != NULL && (*seg)->next != NULL)
	{
	  if (tmp != *seg && (*seg)->type == SLIST && (*seg)->name != NULL && \
	      strcmp((*seg)->name, tmp->name) == 0)
	    {
	      XMLmodifyListInTab(seg, tmp->name);
	      while (*seg != NULL && (*seg)->prev != NULL)
		*seg = (*seg)->prev;
	      tmp = *seg;
	    }
	  if (*seg!= NULL && (*seg)->next != NULL)
	    *seg = (*seg)->next;
	}
      while (*seg != NULL && (*seg)->prev != NULL)
	*seg = (*seg)->prev;
      tmp = tmp->next;
    }
}
