#ifndef		__MOVE_IN_ELEMENT_C__
# define	__MOVE_IN_ELEMENT_C__

# include	"generic_parser.h"
# include	"navigation/movement.h"

// Move the pointed element for the first one of the list
double		nfGoToFirstElement()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  while (g_msg->segment->element->prev != NULL)
    g_msg->segment->element = g_msg->segment->element->prev;
  return (0);
}

// Move the pointed element for the last one of the list
double		nfGoToLastElement()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  while (g_msg->segment->element->next != NULL)
    g_msg->segment->element = g_msg->segment->element->next;
  return (0);
}

// Move the pointed element for the next one of the list
double		nfGoToNextElement()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if (g_msg->segment->element->next == NULL)
    return (-1); // verify error code
  g_msg->segment->element = g_msg->segment->element->next;
  return (0);
}

// Move the pointed element for the previous one of the list
double		nfGoToPreviousElement()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if (g_msg->segment->element->next == NULL)
    return (-1); // verify error code
  g_msg->segment->element = g_msg->segment->element->next;
  return (0);
}

// Move the pointed element for the one that match the speciifyed ID
double		nfGoToIDElement(int id)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (id == 0)
    return (-1); // Verify error code
  /* if (id == g_msg->segment->element->id) */
  /*   return (0); // Verify error or ok code */
  if ((unsigned int)id < g_msg->segment->element->id)
    {
      while (g_msg->segment->element->prev != NULL && g_msg->segment->element->id != (unsigned int)id)
	g_msg->segment->element = g_msg->segment->element->prev;
    }
  if ((unsigned int)id > g_msg->segment->element->id)
    {
      while (g_msg->segment->element->next != NULL && g_msg->segment->element->id != (unsigned int)id)
	g_msg->segment->element = g_msg->segment->element->next;
    }
  if ((unsigned int)id != g_msg->segment->element->id)
    return (-1); // verify error code;
  return (0);
}

// Move the pointed element for the one that match the speciifyed Name
double		nfGoToNameElement(const char *name)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (name == NULL)
    return (-1); // Verify error code
  /* if (strcmp(name, g_msg->segment->element->name) == 0) */
  /*   return (0); // Verify error or ok code */
  while (g_msg->segment->element->prev != NULL)
    g_msg->segment->element = g_msg->segment->element->prev;
  while (g_msg->segment->element->next != NULL && strcmp(name, g_msg->segment->element->name) != 0)
    g_msg->segment->element = g_msg->segment->element->next;
  if (strcmp(name, g_msg->segment->element->name) != 0)
    return (-1); // verify error code;
  return (0);
}

#endif		/* __MOVE_IN_ELEMENT_C__ */
