#ifndef		__DUMP_SEGMENT_C__
# define	__DUMP_SEGMENT_C__

#include	"tree/segment.h"
#include	<unistd.h>
#include	<stdio.h>

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

#endif		/* __DUMP_SEGMENT_C__ */
