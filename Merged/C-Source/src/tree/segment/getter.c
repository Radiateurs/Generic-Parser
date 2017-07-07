#ifndef		__GETTER_SEGMENT_C__
# define	__GETTER_SEGMENT_C__

# include	"tree/segment.h"
# include	<unistd.h>
# include	<stdlib.h>

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

segment		*getIDSegment(segment *seg, unsigned int id)
{
  segment	*ret;

  if (seg == NULL)
    return (NULL);
  ret = seg;
  while (ret->prev != NULL && ret->id != id)
    ret = ret->prev;
  if (ret->id == id)
    return (ret);
  ret = seg;
  while (ret->next != NULL && ret->id != id)
    ret = ret->next;
  if (ret->id == id)
    return (ret);
  return (NULL);
}


#endif		/* __GETTER_SEGMENT_C__ */
