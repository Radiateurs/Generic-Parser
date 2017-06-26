#ifndef		__GETTER_MESSAGE_C__
# define	__GETTER_MESSAGE_C__

# include	"tree/message.h"
# include	<unistd.h>
# include	<stdlib.h>

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

#endif		/* __GETTER_MESSAGE_C__ */
