#ifndef		__ACCESS_ELEMENT_C__
# define	__ACCESS_ELEMENT_C__

# include	"generic_parser.h"
# include	"navigation/access.h"

// Return the pointed element's id.
int		nfGetElementID()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  return (g_msg->segment->element->id);
}

// Return the next pointed element's id.
int		nfGetNextElementID()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  return (g_msg->segment->element->id);
}

// Return the prev pointed element's id.
int		nfGetPreviousElementID()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL \
      || g_msg->segment->element->prev == NULL)
    return (-1);
  return (g_msg->segment->element->prev->id);
}

// Return the first pointed element's id.
int		nfGetFirstElementID()
{
  element	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  tmp = g_msg->segment->element;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  return (tmp->id);
}

// Return the last pointed element's id.
int		nfGetLastElementID()
{
  element	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  tmp = g_msg->segment->element;
  while (tmp->next != NULL)
    tmp = tmp->next;
  return (tmp->id);
}

// Return the pointed element's name
char		*tfGetElementName()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL || \
      g_msg->segment->element->name == NULL)
    return ("");
  return (g_msg->segment->element->name);
}

// Return the next pointed element's name
char		*tfGetNextElementName()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL \
      || g_msg->segment->element->next == NULL || g_msg->segment->element->name == NULL)
    return ("");
  return (g_msg->segment->element->name);
}

// Return the prev pointed element's name
char		*tfGetPreviousElementName()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL \
      || g_msg->segment->element->prev == NULL || g_msg->segment->element->prev->name == NULL)
    return ("");
  return (g_msg->segment->element->prev->name);
}

// Return the first pointed element's name
char		*tfGetFirstElementName()
{
  element	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return ("");
  tmp = g_msg->segment->element;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  if (tmp->name == NULL)
    return ("");
  return (tmp->name);
}

// Return the last pointed element's name
char		*tfGetLastElementName()
{
  element	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return ("");
  tmp = g_msg->segment->element;
  while (tmp->next != NULL)
    tmp = tmp->next;
  if (tmp->name == NULL)
    return ("");
  return (tmp->name);
}

// Return the pointed selement's content 
char		*tfGetElementContent()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL || \
      g_msg->segment->element->content == NULL)
    return ("");
  return (g_msg->segment->element->content);
}

// Return the next pointed selement's content 
char		*tfGetNextElementContent()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL || \
      g_msg->segment->element->next == NULL || g_msg->segment->element->next->content == NULL)
    return ("");
  return (g_msg->segment->element->next->content);
}

// Return the prev pointed selement's content 
char		*tfGetPreviousElementContent()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL || \
      g_msg->segment->element->prev == NULL || g_msg->segment->element->prev->content == NULL)
    return ("");
  return (g_msg->segment->element->prev->content);
}

// Return the first pointed selement's content 
char		*tfGetFirstElementContent()
{
  element	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return ("");
  tmp = g_msg->segment->element;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  if (tmp->content == NULL)
    return ("");
  return (tmp->content);
}

// Return the last pointed selement's content 
char		*tfGetLastElementContent()
{
  element	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return ("");
  tmp = g_msg->segment->element;
  while (tmp->next != NULL)
    tmp = tmp->next;
  if (tmp->content == NULL)
    return ("");
  return (tmp->content);
}

// Return the pointed element's type.
int		nfGetElementType()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  return ((int)g_msg->segment->element->type);
}

// Return the next pointed element's type.
int		nfGetNextElementType()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL || \
      g_msg->segment->element->next == NULL)
    return (-1);
  return ((int)g_msg->segment->element->next->type);
}

// Return the prev pointed element's type.
int		nfGetPreviousElementType()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL || \
      g_msg->segment->element->prev == NULL)
    return (-1);
  return ((int)g_msg->segment->element->prev->type);
}

// Return the first pointed element's type.
int		nfGetFirstElementType()
{
  element	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  tmp = g_msg->segment->element;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  return (tmp->type);
}

// Return the last pointed element's type.
int		nfGetLastElementType()
{
  element	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  tmp = g_msg->segment->element;
  while (tmp->next != NULL)
    tmp = tmp->next;
  return (tmp->type);
}

#endif		/* __ACCESS_ELEMENT_C__ */
