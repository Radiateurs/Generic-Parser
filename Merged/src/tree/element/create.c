#ifndef		__CREATE_ELEMENT_C__
# define	__CREATE_ELEMENT_C__

#include	"tree/element.h"
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>

int		addElement(element **old, element *new)
{
  while (*old != NULL && (*old)->next != NULL)
    *old = (*old)->next;
  if (*old == NULL)
    new->prev = NULL;
  else
    {
      (*old)->next = new;
      new->prev = *old;
    }
  *old = new;
  return (1);
}

int		newElement(element **old, const char *name, unsigned int id, \
			   const char *content, enum e_attr_type type)
{
  element	*new;

  if (!(new = malloc(sizeof(*new))))
    return (0);
  new->next = NULL;
  new->id = id;
  if (name != NULL)
    new->name = strndup(name, 32);
  else
    new->name = NULL;
  new->type = type;
  new->content = strdup(content);
  while (*old != NULL && (*old)->next != NULL)
    *old = (*old)->next;
  if (*old == NULL)
    new->prev = NULL;
  else
    {
      (*old)->next = new;
      new->prev = *old;
    }
  *old = new;
  return (1);
}


#endif		/* __CREATE_ELLEMENT_C__ */

