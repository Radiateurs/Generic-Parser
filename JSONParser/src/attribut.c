#include	"attribut.h"
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>

int		newAttribut(attribut **old, const char *name, unsigned int id, \
			    const char *content, enum e_attr_type type)
{
  attribut	*new;

  if (content == NULL || strlen(content) == 0)
    return (0);
  if (!(new = malloc(sizeof(*new))))
    return (0);
  new->next = NULL;
  new->id = id;
  if (name != NULL)
    new->name = strndup(name, 32);
  else
    new->name = NULL;
  new->content = strdup(content);
  new->type = type;
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

int		deleteIDAttribut(attribut **old, unsigned int id)
{
  attribut	*tmp;
  attribut	*tmp2;

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
  if (tmp->name)
    free(tmp->name);
  if (tmp->content)
    free(tmp->content);
  free(tmp);
  return (1);
}

int		deleteAttributs(attribut **old)
{
  attribut	*tmp;

  if (*old == NULL)
    return (1);
  while ((*old)->prev != NULL)
    *old = (*old)->prev;
  while (*old != NULL)
    {
      tmp = *old;
      *old = (*old)->next;
      free(tmp->content);
      free(tmp);
    }
  return (1);
}

void		dumpAttribut(attribut *att, int depth)
{
  attribut	*tmp;
  int		i = 0;

  if (att == NULL)
    return ;
  tmp = att;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp != NULL)
    {
      i = 0;
      while (i < depth)
	{
	  putchar('\t');
	  i++;
	}
      if (tmp->name != NULL)
	printf("Attribut [id %d] [name %s] [type %d] [content %s]\n", tmp->id, tmp->name, tmp->type, tmp->content);
      else
	printf("Attribut [id %d] [name (null)] [type %d] [content %s]\n", tmp->id, tmp->type, tmp->content);
      tmp = tmp->next;
    }
}

unsigned int	lastAttributID(attribut *attr)
{
  attribut	*tmp;

  if (attr == NULL)
    return (0);
  tmp = attr;
  while (tmp->next != NULL)
    tmp = tmp->next;
  return (tmp->id);
}
