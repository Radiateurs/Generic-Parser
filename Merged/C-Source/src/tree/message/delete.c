#ifndef		__DELETE_MESSAGE_C__
# define	__DELETE_MESSAGE_C__

# include	"tree/message.h"
# include	<unistd.h>
# include	<stdlib.h>

// Delete every messages
int		deleteMessages(message **old)
{
  message	*tmp;

  if (*old == NULL)
    return (0);
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

// Delete a unique message. THe one that match the given ID
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
  if (tmp->prev != NULL && tmp->next != NULL) // If both of the next and prev pointer aren't NULL then it assign their pointer to the new value. 
    //Prev->next point to Next and Next->prev point to Prev
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

#endif		/* __DELETE_MESSAGE_C__ */
