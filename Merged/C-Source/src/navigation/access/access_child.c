#ifndef		__ACCESS_CHILD_C__
# define	__ACCESS_CHILD_C__

# include	"generic_parser.h"

// Return the pointed child's name on the pointed segment.
char		*tfGetChildName()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL \
      || g_msg->segment->child->name == NULL)
    return ("");
  return (g_msg->segment->child->name);
}

// Return the next child's name on the pointed segment.
char		*tfGetNextChildName()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL \
      || g_msg->segment->child->next != NULL || g_msg->segment->child->next->name == NULL)
    return ("");
  return (g_msg->segment->child->next->name);
}

// Return the previous child's name on the pointed segment.
char		*tfGetPreviousChildName()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL \
      || g_msg->segment->child->prev != NULL || g_msg->segment->child->prev->name == NULL)
    return ("");
  return (g_msg->segment->child->prev->name);
}

// Return the first (begin of list) child's name on the pointed segment.
char		*tfGetFirstChildName()
{
  segment	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL)
    return ("");
  tmp = g_msg->segment->child;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  if (tmp->name != NULL)
    return (tmp->name);
  return ("");
}

// Return the last (end of list) child's name on the pointed segment.
char		*tfGetLastChildName()
{
  segment	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL)
    return ("");
  tmp = g_msg->segment->child;
  while (tmp->next != NULL)
    tmp = tmp->next;
  if (tmp->name != NULL)
    return (tmp->name);
  return ("");
}

// Return the pointed child's ID ont the pointed segment.
double		nfGetChildID()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL)
    return (-1);
  return (g_msg->segment->child->id);
}

// Return the next child's id on the pointed segment
double		nfGetNextChildID()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL
      || g_msg->segment->child->next == NULL)
    return (-1);
  return (g_msg->segment->child->next->id);
}

// Return the previous child's id on the pointed segment
double		nfGetPreviousChildID()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL
      || g_msg->segment->child->prev == NULL)
    return (-1);
  return (g_msg->segment->child->prev->id);
}

// Return the first child's id on the pointed segment
double		nfGetFirstChildID()
{
  segment	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL)
    return (-1);
  tmp = g_msg->segment->child;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  return (tmp->id);
}

// Return the last child's id on the pointed segment
double		nfGetLastChildID()
{
  segment	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL)
    return (-1);
  tmp = g_msg->segment->child;
  while (tmp->next != NULL)
    tmp = tmp->next;
  return (tmp->id);
}

#endif		/* __ACCESS_CHILD_C__ */
