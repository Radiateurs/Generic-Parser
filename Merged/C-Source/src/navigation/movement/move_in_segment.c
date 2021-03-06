#ifndef		__MOVE_IN_SEGMENT_C__
# define	__MOVE_IN_SEGMENT_C__

# include	"generic_parser.h"
# include	"navigation/movement.h"

// Move the pointed segment for the hightest one (root - parent of all segment, first of the segment)
double		nfGoToRoot()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  while (g_msg->segment->parent == NULL)
    g_msg->segment = g_msg->segment->parent;
  return (0);
}

// Move the pointed segment for the upper one, its parent.
double		nfGoToParent()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (g_msg->segment->parent == NULL)
    return (-1); // verify error code
  g_msg->segment = g_msg->segment->parent;
  return (0);
}

// Move the pointed segment for the first of the list
double		nfGoToFirstSegment()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  while (g_msg->segment->prev != NULL)
    g_msg->segment = g_msg->segment->prev;
  return (0);
}

// Move the pointed segment for the last of the list
double		nfGoToLastSegment()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  while (g_msg->segment->next != NULL)
    g_msg->segment = g_msg->segment->next;
  return (0);
}

// Move the pointed segment for the next one in the list
double		nfGoToNextSegment()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (g_msg->segment->next == NULL)
    return (-1); // Verify error code
  g_msg->segment = g_msg->segment->next;
  return (0);
}

// Move the pointed segment for the previous one in the list
double		nfGoToPreviousSegment()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (g_msg->segment->prev == NULL)
    return (-1); // Verify error code
  g_msg->segment = g_msg->segment->prev;
  return (0);
}

// Move the pointed segment to the segment that match the specifyed ID
double		nfGoToIDSegment(int id)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (id == 0)
    return (-1); // Verify error code
  /* if (id == g_msg->segment->id) */
  /*   return (0); // Verify error or ok code */
  if ((unsigned int)id < g_msg->segment->id)
    {
      while (g_msg->segment->prev != NULL && g_msg->segment->id != (unsigned int)id)
	g_msg->segment = g_msg->segment->prev;
    }
  if ((unsigned int)id > g_msg->segment->id)
    {
      while (g_msg->segment->next != NULL && g_msg->segment->id != (unsigned int)id)
	g_msg->segment = g_msg->segment->next;
    }
  if ((unsigned int)id != g_msg->segment->id)
    return (-1); // verify error code;
  return (0);
}

// Move the pointed segment to the segment that match the specifyed Name
double		nfGoToNameSegment(const char *name)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (name == NULL)
    return (-1); // Verify error code
  /* if (strcmp(name, g_msg->segment->name) == 0) */
  /*   return (0); // Verify error or ok code */
  while (g_msg->segment->prev != NULL)
    g_msg->segment = g_msg->segment->prev;
  while (g_msg->segment->next != NULL && strcmp(name, g_msg->segment->name) != 0)
    g_msg->segment = g_msg->segment->next;
  if (strcmp(name, g_msg->segment->name) != 0)
    return (-1); // verify error code;
  return (0);
}

// Move the pointed segment to the first TAB encountered
double		nfGoToFirstTab()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  while (g_msg->segment->prev != NULL)
    g_msg->segment = g_msg->segment->prev;
  while (g_msg->segment->next != NULL && g_msg->segment->type != STAB)
    g_msg->segment = g_msg->segment->next;
  if (g_msg->segment->type != STAB)
    return (-1); // verify error code;
  return (0);  
}

// Move the pointed segment to the first list encountered
double		nfGoToFirstList()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  while (g_msg->segment->prev != NULL)
    g_msg->segment = g_msg->segment->prev;
  while (g_msg->segment->next != NULL && g_msg->segment->type != STAB)
    g_msg->segment = g_msg->segment->next;
  if (g_msg->segment->type != STAB)
    return (-1); // verify error code;
  return (0);  
}

#endif		/* __MOVE_IN_SEGMENT_C__*/
