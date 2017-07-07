#ifndef		__CREATE_MESSAGE_C__
# define	__CREATE_MESSAGE_C__

# include	"tree/message.h"
# include	<unistd.h>
# include	<stdlib.h>
# include	<string.h>

// Should had file type and file name
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

#endif		/* __CREATE_MESSAGE_C__*/
