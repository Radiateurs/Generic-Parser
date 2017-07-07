#ifndef		__DELETE_ELEMENT_C__
# define	__DELETE_ELEMENT_C__

#include	"tree/element.h"
#include	<unistd.h>
#include	<stdlib.h>

int		deleteIDElement(element **old, unsigned int id)
{
  element  	*tmp;
  element	*tmp2;

  if (*old == NULL)
    return (0);
  if ((*old)->id == id)
    {
      tmp = ((*old)->next != NULL) ? (*old)->next : ((*old)->prev != NULL) ? (*old)->prev : NULL;
      free(tmp->content);
      free(tmp->name);
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
  free(tmp->content);
  free(tmp->name);
  free(tmp);
  return (1);
}

int		deleteElements(element **old)
{
  element	*tmp;

  if (*old == NULL)
    return (1);
  while ((*old)->prev != NULL)
    *old = (*old)->prev;
  while (*old != NULL)
    {
      tmp = *old;
      *old = (*old)->next;
      free(tmp->content);
      free(tmp->name);
      free(tmp);
    }
  *old = NULL;
  return (1);
}

#endif		/* __DELETE_ELEMENT_C__ */
