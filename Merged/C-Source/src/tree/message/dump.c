#ifndef		__DUMP_MESSAGE_C__
# define	__DUMP_MESSAGE_C__

# include	"tree/message.h"
# include	<unistd.h>
# include	<stdlib.h>
# include	<stdio.h>

// Dump message variable in a generic form on the standard output
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
      printf("Message [id %d] [Name %] [Type %i]\n", tmp->id, (tmp->name == NULL) ? "" : tmp->name, tmp->type);
      dumpSegment(tmp->segment);
      tmp = tmp->next;
    }
}

#endif		/* __DUMP_MESSAGE_C__ */
