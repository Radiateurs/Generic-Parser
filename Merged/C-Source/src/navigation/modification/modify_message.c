#ifndef		__MODIFY_MESSAGE_C__
# define	__MODIFY_MESSAGE_C__

# include	"generic_parser.h"
# include	"navigation/movement.h"

// Delete Part
double		nfDeleteMessages()
{
  if (deleteMessages(&g_msg) == 0)
    return (-1);
  return (0);
}

double		nfDeleteMessage()
{
  if (g_msg == NULL)
    return (-1); // verify error code
  deleteIDMessage(&g_msg, g_msg->id);
  return (0);
}

double		nfDeleteIDMessage(int id)
{
  if (deleteIDMessage(&g_msg, (unsigned int)id) == 0)
    return (-1);
  return (0);
}

double		nfCloneMessage()
{
  message	*new;

  if (g_msg == NULL)
    return (-1);
  new = NULL;
  newMessage(&new, getLastIDMessage(g_msg) + 1);
  
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

#endif		/* __MODIFY_MESSAGE_C__ */
