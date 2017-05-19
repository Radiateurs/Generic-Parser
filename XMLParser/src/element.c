#include	"element.h"
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>

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

int		newElement(element **old, const char *name, unsigned int id)
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
  new->attribut = NULL;
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

int		deleteIDElement(element **old, unsigned int id)
{
  element  	*tmp;
  element	*tmp2;

  if (*old == NULL)
    return (0);
  if ((*old)->id == id)
    {
      tmp = ((*old)->next != NULL) ? (*old)->next : ((*old)->prev != NULL) ? (*old)->prev : NULL;
      deleteAttributs(&(tmp->attribut));
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
  deleteAttributs(&(tmp->attribut));
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
      deleteAttributs(&(tmp->attribut));
      free(tmp->name);
      free(tmp);
    }
  *old = NULL;
  return (1);
}

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
      printf("Element [id %d] [name %s]\n", tmp->id, tmp->name);
      dumpAttribut(tmp->attribut, depth + 1);
      tmp = tmp->next;
    }
}

unsigned int	lastElementID(element *elem)
{
  element	*tmp;

  if (elem == NULL)
    return (0);
  tmp = elem;
  while (tmp->next != NULL)
    tmp = tmp->next;
  return (tmp->id);
}
