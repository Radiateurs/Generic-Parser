#ifndef		__GETTER_ELEMENT_C__
# define	__GETTER_ELEMENT_C__

#include	"tree/element.h"
#include	<unistd.h>

// Returns the highest ID in the list of element.
unsigned int	lastElementID(element *elem)
{
  element	*tmp;
  unsigned int	max;

  max = 1;
  if (elem == NULL)
    return (0);
  tmp = elem;
  while (tmp->next != NULL)
    {
      if (tmp->id > max)
	max = tmp->id;
      tmp = tmp->next;
    }
  tmp = elem;
  while (tmp->prev != NULL)
    {
      if (tmp->id > max)
	max = tmp->id;
      tmp = tmp->prev;
    }
  return (max);
}

// Returns the element that match the ID
element         *getIDElement(element *elem, unsigned int id)
{
  element       *ret;

  if (elem == NULL)
    return (NULL);
  ret = elem;
  while (ret->prev != NULL && ret->id != id)
    ret = ret->prev;
  if (ret->id == id)
    return (ret);
  ret = elem;
  while (ret->next != NULL && ret->id != id)
    ret = ret->next;
  if (ret->id == id)
    return (ret);
  return (NULL);
}

// Count how much element are present in the list
int             countElement(element *elem)
{
  element       *tmp;
  int           total = 1;

  if (elem == NULL)
    return (0);
  tmp = elem;
  while (tmp->prev != NULL)
    {
      tmp = tmp->prev;
      total++;
    }
  tmp = elem;
  while (tmp->next != NULL)
    {
      tmp = tmp->next;
      total++;
    }
  return (total);
}

#endif		/* __GETTER_ELEMENT_C__ */
