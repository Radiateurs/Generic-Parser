#ifndef		__DUMP_ELEMENT_C__
# define	__DUMP_ELEMENT_C__

#include	"tree/element.h"
#include	<unistd.h>
#include	<stdlib.h>
#include	<stdio.h>

// Print the element on the standard output. Can be used has a log or a debug.
// It's printed in a generic way
void		dumpElement(element *elem, int depth)
{
  element	*tmp;
  int		i = 0;

  if (elem == NULL)
    return ;
  tmp = elem;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp)
    {
      i = 0;
      while (i < depth)
	{
	  putchar('\t');
	  i++;
	}
      printf("Element [id %d] [name %s] [type %d] [content %s]\n", tmp->id, tmp->name, tmp->type, tmp->content);
      tmp = tmp->next;
    }
}

#endif		/* __DUMP_ELEMENT_C__ */
