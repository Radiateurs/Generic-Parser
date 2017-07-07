#ifndef		__GETTER_MESSAGE_C__
# define	__GETTER_MESSAGE_C__

# include	"tree/message.h"
# include	<unistd.h>
# include	<stdlib.h>

int		switchToIDMessage(message **old, unsigned int id)
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

unsigned int	getLastIDMessage(message *msg)
{
  message	*tmp;
  unsigned int	max_id;

  max_id = 0;
  if (msg == NULL)
    return (max_id);
  tmp = msg;
  while (tmp->prev != NULL)
    {
      if (tmp->id > max_id)
	max_id = tmp->id;
      tmp = tmp->prev;
    }
  if (tmp->id > max_id)
    max_id = tmp->id;
  tmp = msg;
  while (tmp->next != NULL)
    {
      if (tmp->id > max_id)
	max_id = tmp->id;
      tmp = tmp->next;
    }
  if (tmp->id > max_id)
    max_id = tmp->id;
  return (max_id);
}

#endif		/* __GETTER_MESSAGE_C__ */
