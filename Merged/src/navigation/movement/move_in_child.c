#ifndef		__MOVE_IN_CHILD_C__
# define	__MOVE_IN_CHILD_C__

# include	"generic_parser.h"
# include	"navigation/movement.h"

int		nfGoToFirstChild()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (g_msg->segment->child == NULL)
    return (-1); // Verfiy error code
  while (g_msg->segment->child->prev != NULL)
    g_msg->segment->child = g_msg->segment->child->prev;
  return (0);
}

int		nfGoToLastChild()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (g_msg->segment->child == NULL)
    return (-1); // Verfiy error code
  while (g_msg->segment->child->next != NULL)
    g_msg->segment->child = g_msg->segment->child->next;
  return (0);
}

int		nfGoToNextChild()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (g_msg->segment->child == NULL)
    return (-1); // Verfiy error code
  if (g_msg->segment->child->next == NULL)
    return (-1); // Verify error code
  g_msg->segment->child = g_msg->segment->child->next;
  return (0);
}

int		nfGoToPreviousChild()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (g_msg->segment->child == NULL)
    return (-1); // Verfiy error code
  if (g_msg->segment->child->prev == NULL)
    return (-1); // Verify error code
  g_msg->segment->child = g_msg->segment->child->prev;
  return (0);
}

int		nfGoToIDChild(int id)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (g_msg->segment->child == NULL)
    return (-1); // Verfiy error code
  if (id == 0)
    return (-1); // Verify error code
  /* if (id == g_msg->segment->child->id) */
  /*   return (0); // Verify error or ok code */
  if ((unsigned int)id < g_msg->segment->child->id)
    {
      while (g_msg->segment->child->prev != NULL && g_msg->segment->child->id != (unsigned int)id)
	g_msg->segment->child = g_msg->segment->child->prev;
    }
  if ((unsigned int)id > g_msg->segment->child->id && g_msg->segment->child->id != (unsigned int)id)
    {
      while (g_msg->segment->child->next != NULL)
	g_msg->segment->child = g_msg->segment->child->next;
    }
  if ((unsigned int)id != g_msg->segment->child->id)
    return (-1); // verify error code;
  return (0);
}

int		nfGoToNameChild(const char *name)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (name == NULL)
    return (-1); // Verify error code
  /* if (strcmp(name, g_msg->segment->child->name) == 0) */
  /*   return (0); // Verify error or ok code */
  while (g_msg->segment->child->prev != NULL)
    g_msg->segment->child = g_msg->segment->child->prev;
  while (g_msg->segment->child->next != NULL && strcmp(name, g_msg->segment->child->name) != 0)
    g_msg->segment->child = g_msg->segment->child->next;
  if (strcmp(name, g_msg->segment->child->name) != 0)
    return (-1); // verify error code;
  return (0);
}

#endif		/* __MOVE_IN_CHILD_C__*/
