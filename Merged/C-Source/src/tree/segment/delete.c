#ifndef		__DELETE_SEGMENT_C__
# define	__DELETE_SEGMENT_C__

# include	"tree/segment.h"
# include	<unistd.h>
# include	<stdlib.h>

// Remove (do not free) the child in old with the same id as given in parameter.
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

// Remove (do not free) the segment in old with the same id as given in parameter.
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

// delete (free) the segment in old with the same id as given in parameter.
int		deleteIDSegment(segment **old, unsigned int id)
{
  segment	*tmp;
  segment	*tmp2;

  if (*old == NULL)
    return (0);
  // If already pointing it.
  if ((*old)->id == id)
    {
      tmp = (*old)->next;
      tmp2 = (*old)->prev;
      deleteChildSegment(&((*old)->child));
      deleteElements(&((*old)->element));
      free(*old); 
      if (tmp != NULL)
	tmp->prev = tmp2;
      if (tmp2 != NULL)
	tmp2->next = tmp;
      *old = (tmp == NULL) ? tmp2 : tmp;
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
  deleteChildSegment(&tmp);
  deleteElements(&(tmp->element));
  free(tmp->name);
  free(tmp);
  return (1);
}

// Delete every child in the pointed segment.
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

// Delete every segments. (delete the list and everything in it.)
int		deleteSegments(segment **old)
{
  segment	*tmp;
  
  if (*old == NULL)
    return (-1);
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
  return (0);
}

// Delete the list of segment. (only the list, doesn't go to the higest segment).
int		deleteListSegments(segment **old)
{
  segment	*tmp;
  segment	*next_tmp;
  
  if (*old == NULL)
    return (-1);
  while ((*old)->prev != NULL)
    *old = (*old)->prev;
  tmp = *old;
  *old = (*old)->parent;
  while (tmp != NULL)
    {
      next_tmp = tmp->next;
      deleteChildSegment(&(tmp->child));
      deleteElements(&(tmp->element));
      if (tmp->name != NULL)
	free(tmp->name);
      free(tmp);
      tmp = next_tmp;
    }
  return (0);
}

#endif		/* __DELETE_SEGMENT_C__ */
