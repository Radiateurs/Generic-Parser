#include	"segment.h"
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>

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

segment		*copySegment(segment *to_copy)
{
  segment	*copy;

  if (!(copy = malloc(sizeof(*copy))))
    return (NULL);
  copy->name = strdup(to_copy->name);
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

void		removeIDChild(segment **old, unsigned int id)
{
  segment	*tmp;
  segment	*tmp2;

  if (*old == NULL || (*old)->child == NULL)
    return ;
  tmp = (*old)->child;
  while (tmp->prev != NULL && tmp->id != id)
    tmp = tmp->prev;
  if (tmp->id != id)
    tmp = (*old)->child;
  while (tmp->next != NULL && tmp->id != id)
    tmp = tmp->next;
  if (tmp->id != id)
    return ;
  (*old)->child = tmp;
  tmp = (*old)->child->prev;
  tmp2 = (*old)->child->next;
  if (tmp != NULL)
    tmp->next = tmp2;
  if (tmp2 != NULL)
    tmp2->prev = tmp;
  (*old)->child = (tmp != NULL) ? tmp : tmp2;
  return ;
}

void		removeIDSegment(segment **old, unsigned int id)
{
  segment	*tmp;
  segment	*tmp2;

  if (*old == NULL)
    return ;
  tmp = *old;
  while (tmp->prev != NULL && tmp->id != id)
    tmp = tmp->prev;
  if (tmp->id != id)
    tmp = *old;
  while (tmp->next != NULL && tmp->id != id)
    tmp = tmp->next;
  if (tmp->id != id)
    return ;
  *old = tmp;
  tmp = (*old)->prev;
  tmp2 = (*old)->next;
  if (tmp != NULL)
    tmp->next = tmp2;
  if (tmp2 != NULL)
    tmp2->prev = tmp;
  *old = (tmp == NULL) ? tmp2 : tmp;
  return ;
}

int		deleteIDSegment(segment **old, unsigned int id)
{
  segment	*tmp;
  segment	*tmp2;

  if (*old == NULL)
    return (0);
  if ((*old)->id == id)
    {
      tmp = ((*old)->next != NULL) ? (*old)->next : ((*old)->prev != NULL) ? (*old)->prev : NULL;
      deleteElements(&((*old)->element));
      free(*old);
      *old = tmp;
      return (1);
    }
  tmp = *old;
  while (tmp->prev != NULL && tmp->id != id)
    tmp = tmp->prev;
  if (tmp->id != id)
    tmp = *old;
  while (tmp->next != NULL && tmp->id != id)
    tmp = tmp->next;
  if (tmp->id != id)
    return (0);
  if (tmp->prev != NULL && tmp->next != NULL)
    {
      tmp2 = tmp->prev;
      tmp2->next = tmp->next;
      tmp->next->prev = tmp2;
    }
  else
    {
      if (tmp->next == NULL && tmp->prev != NULL)
	tmp->prev->next = NULL;
      if (tmp->prev == NULL && tmp->next != NULL)
	tmp->next->prev = NULL;
    }
  deleteElements(&(tmp->element));
  free(tmp->name);
  free(tmp);
  return (1);
}

int		deleteChildSegment(segment **old)
{
  segment	*tmp;

  if (*old == NULL)
    return (1);
  while ((*old)->prev != NULL)
    *old = (*old)->prev;
  while (*old != NULL)
    {
      tmp = *old;
      *old = (*old)->next;
      deleteChildSegment(&(tmp->child));
      deleteElements(&(tmp->element));
      if (tmp->name != NULL)
	free(tmp->name);
      free(tmp);
    }
  return (1);
}

int		deleteSegments(segment **old)
{
  segment	*tmp;
  
  if (*old == NULL)
    return (1);
  while ((*old)->parent != NULL)
    *old = (*old)->parent;
  while ((*old)->prev != NULL)
    *old = (*old)->prev;
  while (*old != NULL)
    {
      tmp = *old;
      *old = (*old)->next;
      deleteChildSegment(&(tmp->child));
      deleteElements(&(tmp->element));
      if (tmp->name != NULL)
	free(tmp->name);
      free(tmp);
    }
  return (1);
}

unsigned int	lastSegmentID(segment *seg)
{
  segment	*tmp;

  if (!seg)
    return (0);
  tmp = seg;
  while (tmp->next != NULL)
    tmp = tmp->next;
  return (tmp->id);
}

void		dumpSegmentChild(segment *seg)
{
  segment	*tmp;
  int		i;

  if (seg == NULL)
    return ;
  tmp = seg;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp)
    {
      i = 0;
      while (i < tmp->depth)
	{
	  putchar('\t');
	  i++;
	}
      if (tmp->type == SSEG)
	printf("Segment ");
      else
	{
	  if (tmp->type == SLIST)
	    printf("List ");
	  else
	    printf("Tab ");
	}
      printf("[group id %d] [name %s] [depth %i]\n", tmp->id, (tmp->name == NULL) ? "NULL" : tmp->name, tmp->depth);
      dumpElement(tmp->element, tmp->depth + 1);
      dumpSegmentChild(tmp->child);
      tmp = tmp->next;
    }
}

void		dumpSegment(segment *seg)
{
  segment	*tmp;
  int		i = 0;

  if (seg == NULL)
    return ;
  tmp = seg;
  while (tmp->parent != NULL)
    tmp = tmp->parent;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp)
    {
      i = 0;
      while (i < tmp->depth)
	{
	  putchar('\t');
	  i++;
	}
      if (tmp->type == SSEG)
	printf("Segment ");
      else
	{
	  if (tmp->type == SLIST)
	    printf("List ");
	  else
	    printf("Tab ");
	}
      printf("[group id %d] [name %s] [depth %i]\n", tmp->id, (tmp->name == NULL) ? "NULL" : tmp->name, tmp->depth);
      dumpElement(tmp->element, tmp->depth + 1);
      dumpSegmentChild(tmp->child);
      tmp = tmp->next;
    }
}

unsigned int	lastGroupID(segment *seg)
{
  segment	*tmp;
 
  tmp = seg;
  if (tmp->is_a_group)
    return (tmp->id);
  while (tmp->parent != NULL && !tmp->is_a_group)
    tmp = tmp->parent;
  return (tmp->id);
}

unsigned int	getNextID(segment *seg)
{
  element	*etmp; // Element temp
  segment	*stmp; // Segment temp
  unsigned int	eid = 0; // Element ID
  unsigned int	sid = 0; // Segment ID

  if (seg == NULL)
    return (1);
  etmp = seg->element;
  stmp = seg->child;
  while (etmp != NULL)
    {
      if (etmp->id > eid)
	eid = etmp->id;
      etmp = etmp->next;
    }
  while (stmp != NULL)
    {
      if (stmp->id > sid)
	sid = stmp->id;
      stmp = stmp->next;
    }
  return (eid + sid + 1);
}

void		closeGroupSegment(segment **seg)
{
  if ((*seg)->parent == NULL)
    return ;
  *seg = (*seg)->parent;
  return ;
}

segment		*getParent(segment *seg)
{
  return (seg->parent);
}

int		countSegment(segment *seg)
{
  int		i = 0;
  segment	*tmp;

  tmp = seg;
  while (tmp != NULL)
    {
      i++;
      tmp = tmp->prev;
    }
  if (seg != NULL)
    tmp = seg->next;
  while (tmp != NULL)
    {
      i++;
      tmp = tmp->next;
    }
  return (i);
}
