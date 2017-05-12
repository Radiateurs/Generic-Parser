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
			   int depth)
{
  segment	*new;

  if (!(new = malloc(sizeof(*new))))
    return (0);
  new->id = id;
  new->child = NULL;
  new->depth = depth;
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

  if (seg == NULL)
    return ;
  tmp = seg;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp)
    {
      if (tmp->is_a_group)
	printf("Segment Group [group id %d] [name %s] [depth %i]\n", tmp->id, tmp->name, tmp->depth);
      else
	printf("Segment container [id %d] [name %s] [depth %i]\n", tmp->id, tmp->name, tmp->depth);
      dumpElement(tmp->element);
      dumpSegmentChild(tmp->child);
      tmp = tmp->next;
    }
}

void		dumpSegment(segment *seg)
{
  segment	*tmp;

  if (seg == NULL)
    return ;
  tmp = seg;
  while (tmp->parent != NULL)
    tmp = tmp->parent;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp)
    {
      if (tmp->is_a_group)
	printf("Segment Group [group id %d] [name %s]\n", tmp->id, tmp->name);
      else
	printf("Segment container [id %d] [name %s]\n", tmp->id, tmp->name);
      dumpElement(tmp->element);
      dumpSegmentChild(tmp->child);
      tmp = tmp->next;
    }
}

char		*getParentName(segment *seg)
{
  if (seg == NULL || seg->parent == NULL)
    return (NULL);
  return (seg->parent->name);
}

int		findInChilds(segment *seg, char *name)
{
  segment	*tmp;

  if (seg == NULL)
    return (0);
  tmp = seg;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp)
    {
      if (strcmp(name, tmp->name) == 0)
	return (1);
      if (findInChilds(tmp->child, name) == 1)
	return (1);
      tmp = tmp->next;
    }
  return (0);
}

int		findSegmentByName(segment *seg, char *name)
{
  segment	*tmp;

  if (seg == NULL)
    return (0);
  tmp = seg;
  while (tmp->parent != NULL)
    tmp = tmp->parent;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp)
    {
      if (strcmp(name, tmp->name) == 0)
	return (1);
      if (findInChilds(tmp->child, name) == 1)
	return (1);
      tmp = tmp->next;
    }
  return (0);
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

void		closeGroupSegment(segment **seg)
{
  if ((*seg)->parent == NULL)
    return ;
  *seg = (*seg)->parent;
  return ;
}
