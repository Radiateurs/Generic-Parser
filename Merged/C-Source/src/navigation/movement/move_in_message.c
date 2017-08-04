#ifndef		__MOVE_IN_MESSAGE_C__
# define	__MOVE_IN_MESSAGE_C__

# include	<string.h>
# include	"generic_parser.h"

// Move the pointed message to the first message of the list
double		nfGoToFirstMessage()
{
  if (g_msg == NULL)
    return (-1); // verify error code
  while (g_msg->prev != NULL)
    g_msg = g_msg->prev;
  return (0);
}

// Move the pointed message to the last message of the list
double		nfGoToLastMessage()
{
  if (g_msg == NULL)
    return (-1); // verify error code
  while (g_msg->next != NULL)
    g_msg = g_msg->next;
  return (0);
}

// Move the pointed message to the previous message in the list
double		nfGoToPreviousMessage()
{
  if (g_msg == NULL || g_msg->prev != NULL)
    return (-1); // verify error code
  g_msg = g_msg->prev;
  return (0);
}

// Move the pointed message to the next message in the list
double		nfGoToNextMessage()
{
  if (g_msg == NULL || g_msg->next != NULL)
    return (-1); // verify error code
  g_msg = g_msg->next;
  return (0);
}

// Move the pointed message to the first message that match the specifyed ID
double		nfGoToIDMessage(int id)
{
  message	*tmp;

  if (g_msg == NULL)
    return (-1); // Verify error code
  tmp = g_msg;
  while (tmp->next != NULL && tmp->id != (unsigned int)id)
    tmp = tmp->next;
  while (tmp->prev != NULL && tmp->id != (unsigned int)id)
    tmp = tmp->prev;
  if (tmp->id != (unsigned int)id)
    return (-1); // verify error code
  g_msg = tmp;
  return (0);
}

// Move the pointed message to the first message that match the specifyed type
double		nfGoToTypeMessage(int type)
{
  message	*tmp;

  if (g_msg == NULL)
    return (-1); // Verify error code
  tmp = g_msg;
  while (tmp->next != NULL && tmp->type != (enum e_msg_type)type)
    tmp = tmp->next;
  while (tmp->prev != NULL && tmp->type != (enum e_msg_type)type)
    tmp = tmp->prev;
  if (tmp->type != (enum e_msg_type)type)
    return (-1); // verify error code
  g_msg = tmp;
  return (0);
}

// Move the pointed message to the first message that match the specifyed name.
double		nfGoToNameMessage(char *name)
{
  message	*tmp;

  if (g_msg == NULL)
    return (-1); // Verify error code
  tmp = g_msg;
  while (tmp->next != NULL && strcmp(g_msg->name, name) != 0)
    tmp = tmp->next;
  while (tmp->prev != NULL && strcmp(g_msg->name, name) != 0)
    tmp = tmp->prev;
  if (strcmp(g_msg->name, name) != 0)
    return (-1); // verify error code
  g_msg = tmp;
  return (0);
}

#endif		/* __MOVE_IN_MESSAGE_C__ */
