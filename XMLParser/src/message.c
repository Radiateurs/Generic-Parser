#include	"message.h"
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>

int		newMessage(message **old, unsigned int id)
{
  message	*new;

  if (!(new = malloc(sizeof(*new))))
    return (0);
  new->id = id;
  new->next = NULL;
  new->segment = NULL;
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

int		deleteMessages(message **old)
{
  message	*tmp;

  while ((*old)->prev != NULL)
    *old = (*old)->prev;
  tmp = *old;
  while (*old)
    {
      tmp = *old;
      *old = (*old)->next;
      deleteSegments(&(tmp->segment));
      free(tmp);
    }
  *old = tmp;
  return (1);
}

int		deleteIDmessage(message **old, unsigned int id)
{
  message	*tmp;
  message	*tmp2;

  if (*old == NULL)
    return (0);
  if (*old != NULL && (*old)->id == id)
    {
      tmp = ((*old)->next != NULL) ? (*old)->next : ((*old)->prev != NULL) ? (*old)->prev : NULL;
      deleteSegments(&((*old)->segment));
      free(*old);
      *old = tmp;
      return (1);
    }
  tmp = *old;
  while (tmp != NULL && tmp->prev != NULL && tmp->id != id)
    tmp = tmp->prev;
  if (tmp->id != id)
    tmp = *old;
  while (tmp != NULL && tmp->next != NULL && tmp->id != id)
    tmp = tmp->next;
  if (tmp == NULL || tmp->id != id)
    return (1);
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
  deleteSegments(&(tmp->segment));
  free(tmp);
  return (1);
}

int		switchToIDMessage(message **old, double id)
{
  message	*tmp;

  if (*old == NULL)
    return (0);
  tmp = *old;
  while ((*old)->prev != NULL && (*old)->id != id)
    *old = (*old)->prev;
  if ((*old)->id == id)
    return (1);
  *old = tmp;
  while ((*old)->next != NULL && (*old)->id != id)
    *old = (*old)->next;
  if ((*old)->id == id)
    return (1);
  *old = tmp;
  return (0);  
}

void		dumpMessage(message *msg)
{
  message	*tmp;

  if (msg == NULL)
    return ;
  tmp = msg;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp)
    {
      printf("Message [id %d]\n", tmp->id);
      dumpSegment(tmp->segment);
      tmp = tmp->next;
    }
}
