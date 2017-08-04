#ifndef		__MODIFY_MESSAGE_C__
# define	__MODIFY_MESSAGE_C__

# include	"generic_parser.h"
# include	"navigation/movement.h"

// Delete All the messages
double		nfDeleteMessages()
{
  if (deleteMessages(&g_msg) == 0)
    return (-1);
  return (0);
}

// Delete the pointed message and all inside.
double		nfDeleteMessage()
{
  if (g_msg == NULL)
    return (-1); // verify error code
  deleteIDmessage(&g_msg, g_msg->id);
  return (0);
}

double		nfDeleteIDMessage(int id)
{
  if (deleteIDmessage(&g_msg, (unsigned int)id) == 0)
    return (-1);
  return (0);
}

// Copy the pointed message into a new one.
double		nfCopyMessage()
{
  message	*tmp;

  if (g_msg == NULL)
    return (-1);
  tmp = g_msg; 
  newMessage(&g_msg, getLastIDMessage(g_msg) + 1);
  g_msg->segment = cloneSegment(tmp->segment);
  return (0);
}

// Create a new message that contain the same segment's adress.
// When an element is modifyed in the original message it is also modifyed in the mirrored one.
double		nfMirrorMessage()
{
  message	*tmp;

  if (g_msg == NULL)
    return (-1); // VERIFY
  tmp = g_msg;
  if (newMessage(&g_msg, getLastIDMessage(g_msg) + 1) == 0)
    return (-1);
  g_msg->segment = tmp->segment;
  return (0);
}

// Create a new message
double		nfAddMessage(const char *name, int type)
{
  if (newMessage(&g_msg, getLastIDMessage(g_msg)) == -1)
    return (-1);
  g_msg->name = strdup(name);
  g_msg->type = (enum e_msg_type)type;
  return (0);
}

// Modify the pointed message's name
double		nfModifyMessageName(const char *new_name)
{
  if (g_msg == NULL)
    return (-1); // Verify error code.
  if (g_msg->name != NULL)
    free(g_msg->name);
  g_msg->name = strdup(new_name);
  return (0);
}

#endif		/* __MODIFY_MESSAGE_C__ */
