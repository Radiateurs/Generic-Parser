#include	"segment.h"
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>

int		addChild(segment **old, segment *child)
{
  if ((*old)->child == NULL)
    {
      (*old)->child = child;
      return (1);
    }
  *old = (*old)->child;
  while ((*old)->next != NULL)
    *old = (*old)->next;
  (*old)->next = child;
  child->prev = *old;
  return (1);
}

int		newSegment(segment **old, const char *name, unsigned int id, int is_a_group, int is_a_child, \
			   int depth, int segType)
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
	  new->parent = *old;
	  new->prev = NULL;
	  addChild(old, new);
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
      printf("[group id %d] [name %s] [depth %i]\n", tmp->id, tmp->name, tmp->depth);
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
      printf("[group id %d] [name %s] [depth %i]\n", tmp->id, tmp->name, tmp->depth);
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
  element	*etmp;
  segment	*stmp;
  unsigned int	eid = 0;
  unsigned int	sid = 0;

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
  if (sid > eid)
    return (sid + 1);
  if (eid > sid)
    return (eid + 1);
  return (1);
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
