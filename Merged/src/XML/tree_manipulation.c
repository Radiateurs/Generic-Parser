#ifndef		__XML_TREE_MANIPULATION_C__
# define	__XML_TREE_MANIPULATION_C__

# include	"XMLParser.h"

/*
** Return 1 if the segment doesn't have text data element
** Return 0 if there is
*/
int		segmentHasNoText(segment *seg)
{
  element	*tmp;

  if (seg == NULL)
    return (0);
  if (seg->element == NULL)
    return (1);
  tmp = seg->element;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp)
    {
      if (tmp->name[0] == g_text)
	return (0);
      if (tmp->next == NULL)
	return (1);
      tmp = tmp->next;
    }
  return (1);
}

/*
** Identify the token type. For XML the only handled type is STRING | ALPHANUM ("DATA")
*/
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

/*
** Add a segment in the tree
*/
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

/*
** Add a chunk (understand data parts yet identify)
*/
void		XMLadd_chunk_to_tree(XMLtree_parser *info, message **msg)
{
  char		*tmp;

  switch ((*info).current_tree_type)
    {
    case CLOSEGROUP:
      // For XML it will be a '/' token.
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
      // Useless. Unless there is an actual attribut w/ value
      // <example data=""/>
      if ((*info).elem_name[0] != g_text)
	{
	  (*info).seg_name = malloc(sizeof(char) * 2);
	  (*info).seg_name[0] = g_attribut;
	  (*info).seg_name[1] = '\0';
	  tmp = mconcat((*info).seg_name, (*info).elem_name);
	  free((*info).elem_name);
	  free((*info).seg_name);
	  (*info).elem_name = strdup(tmp);
	  free(tmp);
	  (*info).seg_name = NULL;
	}
      newElement(&((*msg)->segment->element), (*info).elem_name, getNextID((*msg)->segment), \
		 "TESTEUH", STRING);
      if ((*info).elem_name != NULL)
	free((*info).elem_name);
      (*info).elem_name = NULL;
      (*info).last_tree_type = (*info).current_tree_type;
      (*info).current_tree_type = NOPE;
      break;
    case ATTRIBUT:
      // Add an attribut. Understand a tree element with it's content
      if ((*info).content == NULL)
	return ;
      if (((*msg)->segment != NULL && (*msg)->segment->element == NULL) || (*info).elem_name != NULL)
	if (newElement(&((*msg)->segment->element), (*info).elem_name,	\
		       getNextID((*msg)->segment), (*info).content, (*info).value_type) != 1)
	  {
	    (*info).current_state = ERROR;
	    return ;
	  }
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

/*
** Init a segment to be the parent of identical segment that are in the same depth.
** Ex : there is four <example/> tags in the root segment.
** After passing in ModifyListInTab the four same tag will be with no name and their new parent (<example>)
** will be a TAB segment.
*/
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

/*
** This function scroll through all segment in the range of old_parent and add those with childs_name's name
** in new_parent. Once done, new_parent is added in old_parent and the the added segment are removed from 
** old_parent.
*/
int		XMLmodifyListInTab(segment **old_parent, const char *childs_name)
{
  segment	*tmp;
  segment	*new_parent;
  int		for_ids;
  int	        on_off = 0;

  // Init of new_parent.
  new_parent = initNewParent(old_parent, childs_name);
  while (*old_parent != NULL && (*old_parent)->prev != NULL)
    *old_parent = (*old_parent)->prev;
  // on_off is a "switch" when the algo reached the end of the list.
  while (on_off == 0)
    {
      if (*old_parent != NULL && *old_parent != new_parent && (*old_parent)->type == SLIST \
	  && (*old_parent)->name != NULL				\
	  && strcmp((*old_parent)->name, new_parent->name) == 0)
	{
	  // A segment has been found.
	  (*old_parent)->depth++;
	  // increase by one the depth of all child inside the pointed segment.
	  increaseChildDepth(old_parent);
	  free((*old_parent)->name);
	  (*old_parent)->name = NULL;
	  tmp = *old_parent;
	  // Remove the segment previously found from old_parent.
	  removeIDSegment(old_parent, (*old_parent)->id);
	  tmp->id = getNextID(new_parent);
	  // add the segment in new_parent
	  addChild(&new_parent, tmp);
	  // go back to start.
	  while (*old_parent != NULL && (*old_parent)->prev != NULL)
	    *old_parent = (*old_parent)->prev;
	  // Cause we found a segment to add in new_parent we go back to start and skip the 
	  // increasement in the list (to stay at the begin of the list).
	  continue ;
	}
      if (*old_parent == NULL || (*old_parent)->next == NULL)
	on_off = 1;
      else
	*old_parent = (*old_parent)->next;
    }
  // Add new_parent in old_parent.
  addSegment(old_parent, new_parent, 0);
  // Rewrite the ids in each segment.
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

/*
** Look for identical segment in a saegment list.
** if too (or more) segment have the same name, it means that they should be in a parent
** the new parent should have their name and the new child doesn't have name.
*/
void		XMLfindAndModifyListInTab(segment **seg)
{
  segment	*tmp;

  // Go to the start of all segments (root)
  if (seg == NULL || (*seg) == NULL)
    return ;
  while (*seg != NULL && (*seg)->prev != NULL)
    *seg = (*seg)->prev;
  // Look for any segment that aren't TAB and do a recursive with their child. (send child in verification)
  while (*seg != NULL)
    {
      if ((*seg)->type != STAB)
	XMLfindAndModifyListInTab(&((*seg)->child));
      if ((*seg)->next == NULL)
	break;
      *seg = (*seg)->next;
    }
  // Once done, go the the begin.
  while (*seg != NULL && (*seg)->prev != NULL)
    *seg = (*seg)->prev;
  // save the first position in tmp.
  tmp = *seg;
  while (tmp != NULL)
    {
      while (*seg != NULL && (*seg)->next != NULL)
	{
	  // If the saved segment (tmp) has the same name than the pointed moving segment (seg)
	  // it means that we've found a match.
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

#endif		/* __XML_TREE_MANIPULATION_C__ */
