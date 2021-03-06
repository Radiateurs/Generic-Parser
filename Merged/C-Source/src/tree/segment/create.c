#ifndef		__CREATE_SEGMENT_C__
# define	__CREATE_SEGMENT_C__

# include	"tree/segment.h"
# include	<unistd.h>
# include	<stdlib.h>
# include	<string.h>

// Create a segment and initialize every variable with the matching given ones.
segment		*initSegment(const char *name, unsigned int id, int is_a_group, int depth, int segType)
{
  segment	*new;

  if (!(new = malloc(sizeof(*new))))
    return (0);
  new->id = id;
  new->child = NULL;
  new->depth = depth;
  new->type = segType;
  new->is_a_group = is_a_group;
  if (name != NULL)
    new->name = strndup(name, 32);
  else
    new->name = NULL;
  new->element = NULL;
  new->next = NULL;
  new->prev = NULL;
  return (new);
}

/*
** Add the segment child as a child in the old segment and keep the old pointer on the same position.
*/
int		addChild(segment **old, segment *child)
{
  child->parent = *old;
  child->prev = NULL;
  child->next = NULL;
  // If there isn't child in old, the child segment 
  // is added as the first and only child for now.
  if ((*old)->child == NULL)
    {
      (*old)->child = child;
      return (1);
    }
  // Else the segment child is added at the end of the child list of old.
  while ((*old)->child->next != NULL) // Go to the end of list.
    (*old)->child = (*old)->child->next;
  (*old)->child->next = child;
  child->prev = (*old)->child;
  return (1);
}

/*
** Add a segment already allocated as next or as a child. This is specified by 
** the int is_a_child. If is a child is equal to 1 or more the added segment is a child.
** If is_a_child is equal to 0 the added segment will be in the same list as old.
*/
int		addSegment(segment **old, segment *to_add, int is_a_child)
{
  if (is_a_child > 0)
    {
      addChild(old, to_add);
      *old = to_add;
      return (1);
    }
  else
    {
      if (*old == NULL)
	{
	  to_add->next = NULL;
	  to_add->prev = NULL;
	  *old = to_add;
	}
      else
	{
	  to_add->parent = (*old)->parent;
	  to_add->depth = (*old)->depth;
	  while ((*old)->next != NULL)
	    *old = (*old)->next;
	  (*old)->next = to_add;
	  to_add->prev = *old;
	  to_add->next = NULL;
	}
    }
  return (1);
}

/*
** Create a new segment in old as next or as a child.
** The specification is made by is_a_child paramter.
** All other parameters are essential and used to create the new segment.
*/
int		newSegment(segment **old, const char *name, unsigned int id, int is_a_group, int is_a_child, \
			   int depth, int segType)
{
  segment	*new;

  new = initSegment(name, id, is_a_group, depth, segType);
  while (*old != NULL && (*old)->next != NULL)
    *old = (*old)->next;
  if (*old == NULL)
    {
      new->parent = NULL;
      new->prev = NULL;
    }
  else
    {
      if (is_a_child > 0)
	{
	  addChild(old, new);
	  *old = new;
	  return (1);
	}
      else
	{
	  new->parent = (*old)->parent;
	  (*old)->next = new;
	  new->prev = *old;
	}
    }
  *old = new;
  return (1);
}

// Increase the depth of +1 value from the given segment through the end of the depth. (Left to right, top to bottom)
void		increaseChildDepth(segment **seg)
{
  segment	*tmp;

  tmp = *seg;
  while (tmp != NULL && tmp->child != NULL && tmp->child->prev != NULL)
    tmp->child = tmp->child->prev;
  while (tmp != NULL && tmp->child != NULL)
    {
      tmp->child->depth = tmp->depth + 1;
      increaseChildDepth(&(tmp->child->child));
      if (tmp->child->next == NULL)
	return ;
      tmp->child = tmp->child->next;
    }
}

// Create a copy of the segment (only the node)
segment		*copySegment(segment *to_copy)
{
  segment	*copy;

  if (!(copy = malloc(sizeof(*copy))))
    return (NULL);
  if (to_copy == NULL)
    return (NULL);
  if (to_copy->name != NULL)
    copy->name = strdup(to_copy->name);
  if (to_copy->name == NULL)
    copy->name = NULL;
  copy->next = NULL;
  copy->prev = NULL;
  copy->depth = to_copy->depth;
  copy->type = to_copy->type;
  copy->id = to_copy->id;
  copy->is_a_group = to_copy->is_a_group;
  copy->child = to_copy->child;
  copy->element = to_copy->element;
  return (copy);
}

// Close the group. Goes the parent.
void		closeGroupSegment(segment **seg)
{
  if ((*seg)->parent == NULL)
    return ;
  *seg = (*seg)->parent;
  return ;
}

// Old is the one that will contains the cloned segments from origin
void		cloneChild(segment **old, segment *origin)
{
  segment	*tmp;

  while (origin != NULL && origin->prev != NULL)
    origin = origin->prev;
  while (origin != NULL)
    {
      tmp = copySegment(origin);
      tmp->child = NULL;
      tmp->element = NULL;
      tmp->parent = NULL;
      tmp->element = cloneElement(origin->element);
      addChild(old, tmp);
      cloneChild(&((*old)->child), origin->child);
      if (origin->next == NULL)
	return ;
      origin = origin->next;
    }
  return ;
}

// copy the enitre list. Not like copySegement that copy only a node.
segment		*cloneSegment(segment *origin)
{
  segment	*to_return;
  segment	*tmp;

  to_return = NULL;
  while (origin != NULL && origin->parent != NULL)
    origin = origin->parent;
  while (origin != NULL && origin->prev != NULL)
    origin = origin->prev;
  while (origin != NULL)
    {
      tmp = copySegment(origin);
      if (tmp == NULL)
	return (NULL);
      tmp->parent = NULL;
      tmp->child = NULL;
      tmp->element = cloneElement(origin->element);
      cloneChild(&tmp, origin);
      addSegment(&to_return, tmp, 0);
      if (origin->next == NULL)
	return (to_return);
      origin = origin->next;
    }
  return (to_return);
}

#endif		/* __CREATE_SEGMENT_C__ */
