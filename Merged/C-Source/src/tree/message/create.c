#ifndef		__CREATE_MESSAGE_C__
# define	__CREATE_MESSAGE_C__

# include	"tree/message.h"
# include	<unistd.h>
# include	<stdlib.h>
# include	<string.h>

// Add a message at the end of old's list
int		addMessage(message **old, message *new)
{
  if (new == NULL)
    return (-1);
  new->next = NULL;
  if (*old == NULL)
    {
      new->prev = NULL;
      *old = new;
      return (0);
    }
  while ((*old)->next != NULL)
    *old = (*old)->next;
  (*old)->next = new;
  new->prev = *old;
  *old = new;
  return (0);
}

// Should had file type and file name
int		newMessage(message **old, unsigned int id)
{
  message	*new;

  if (!(new = malloc(sizeof(*new))))
    return (-1);
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
  return (0);
}

#endif		/* __CREATE_MESSAGE_C__*/
