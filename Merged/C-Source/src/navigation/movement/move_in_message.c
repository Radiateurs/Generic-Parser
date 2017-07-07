#ifndef		__MOVE_IN_MESSAGE_C__
# define	__MOVE_IN_MESSAGE_C__

# include	"generic_parser.h"

int		nfGoToFirstMessage()
{
  if (g_msg == NULL)
    return (-1); // verify error code
  while (g_msg->prev != NULL)
    g_msg = g_msg->prev;
  return (0);
}

int		nfGoToLastMessage()
{
  if (g_msg == NULL)
    return (-1); // verify error code
  while (g_msg->next != NULL)
    g_msg = g_msg->next;
  return (0);
}

int		nfGoToPreviousMessage()
{
  if (g_msg == NULL || g_msg->prev != NULL)
    return (-1); // verify error code
  g_msg = g_msg->previous;
  return (0);
}

int		nfGoToNextMessage()
{
  if (g_msg == NULL || g_msg->next != NULL)
    return (-1); // verify error code
  g_msg = g_msg->next;
  return (0);
}

int		nfGoToIDMessage(int id)
{
  message	*tmp;

  if (g_msg == NULL)
    return (-1); // Verify error code
  tmp = g_msg;
  while (tmp->next != NULL && tmp->id != id)
    tmp = tmp->next;
  while (tmp->prev != NULL && tmp->id != id)
    tmp = tmp->prev;
  if (tmp->id != id)
    return (-1); // verify error code
  g_msg = tmp;
  return (0);
}

#endif		/* __MOVE_IN_MESSAGE_C__ */
