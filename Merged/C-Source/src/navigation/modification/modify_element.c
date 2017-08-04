#ifndef		__MODIFY_ELEMENT_C__
# define	__MODIFY_ELEMENT_C__

# include	"generic_parser.h"
# include	"navigation/movement.h"

// Delete the pointed element
double		nfDeleteElement()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if (deleteIDElement(&(g_msg->segment->element), g_msg->segment->element->id) == 0)
    return (-1); // Verify error code
  return (0);
}

// Delete evey element
double		nfDeleteAllElement()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if (deleteElements(&(g_msg->segment->element)) == 0)
    return (-1);
  return (0);
}

// Delete the specifyed element by its id
double		nfDeleteIDElement(int id)
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if (deleteIDElement(&(g_msg->segment->element), id) == 0)
    return (-1);
  return (0);
}

// Delete the specifyed element by its Name
double		nfDeleteNameElement(const char *name)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if ((error_return = nfGoToNameElement(name)) != 0)
    return (error_return);
  if (deleteIDElement(&(g_msg->segment->element), g_msg->segment->element->id) == 0)
    return (-1);
  return (0);
}

// Modify the pointed element
double		nfModifyElement(const char *new_name, const char *new_content, int type)
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if (new_name != NULL && strcmp(new_name, "") != 0)
    {
      free(g_msg->segment->element->name);
      g_msg->segment->element->name = strdup(new_name);
    }
  if (new_content != NULL && strcmp(new_content, "") != 0 && type != UNKNOW)
    {
      free(g_msg->segment->element->content);
      g_msg->segment->element->content = strdup(new_content);
      g_msg->segment->element->type = type;
    }
  return (0);
}

// Modify the pointed element's id
double		nfModifyElementID(int new_id)
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if (new_id > 0)
    g_msg->segment->element->id = new_id;
  return (0);
}

// Modify the id of the specified element by its id
double		nfModifyIDElementID(int id, int new_id)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if ((error_return = nfGoToIDElement(id)) != 0)
    return (error_return);
  if (new_id > 0)
    g_msg->segment->element->id = new_id;
  return (0);
}

// Modify the id of the specified element by its name
double		nfModifyNameElementID(const char *name, int new_id)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if ((error_return = nfGoToNameElement(name)) != 0)
    return (error_return);
  if (new_id > 0)
    g_msg->segment->element->id = new_id;
  return (0);
}

// Modify the pointed element's name
double		nfModifyElementName(const char *new_name)
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if (new_name != NULL && strcmp(new_name, "") != 0)
    {
      free(g_msg->segment->element->name);
      g_msg->segment->element->name = strdup(new_name);
    }
  return (0);
}

// Modify the name of the specified element by its id
double		nfModifyIDElementName(int id, const char *new_name)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if ((error_return = nfGoToIDElement(id)) != 0)
    return (error_return);
  if (new_name != NULL && strcmp(new_name, "") != 0)
    {
      free(g_msg->segment->element->name);
      g_msg->segment->element->name = strdup(new_name);
    }
  return (0);
}

// Modify the name of the specified element by its name
double		nfModifyNameElementName(const char *name, const char *new_name)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if ((error_return = nfGoToNameElement(name)) != 0)
    return (error_return);
  if (new_name != NULL && strcmp(new_name, "") != 0)
    {
      free(g_msg->segment->element->name);
      g_msg->segment->element->name = strdup(new_name);
    }
  return (0);
}

// Modify the pointed element's content
double		nfModifyElementContent(const char *new_content, int type)
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if (new_content != NULL && strcmp(new_content, "") != 0)
    {
      free(g_msg->segment->element->content);
      g_msg->segment->element->content = strdup(new_content);
    }
  if (type > -1 && type < 11)
    g_msg->segment->element->type = (enum e_attr_type)type;
  return (0);
}

// Modify the content of the specified element by its id
double		nfModifyIDElementContent(int id, const char *new_content, int type)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if ((error_return = nfGoToIDElement(id)) != 0)
    return (error_return);
  if (new_content != NULL && strcmp(new_content, "") != 0)
    {
      free(g_msg->segment->element->content);
      g_msg->segment->element->content = strdup(new_content);
    }
  if (type > -1 && type < 11)
    g_msg->segment->element->type = (enum e_attr_type)type;
  return (0);
}

// Modify the content of the specified element by its name
double		nfModifyNameElementContent(const char *name, const char *new_content, int type)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if ((error_return = nfGoToNameElement(name)) != 0)
    return (error_return);
  if (new_content != NULL && strcmp(new_content, "") != 0)
    {
      free(g_msg->segment->element->content);
      g_msg->segment->element->content = strdup(new_content);
    }
  if (type > -1 && type < 11)
    g_msg->segment->element->type = (enum e_attr_type)type;
  return (0);
}

// Add an element at the end of the list of the pointed element inside the pointed segment.
// If the pointed element is NULL (understand that there is no element)
// The element will create a new element list on the pointed segment.
// new_id is important. If its value is 0, it will be automatically setted to the last ID available.
// If its value is already in the list of element, it will be modifyed and will receive an available ID.
// Content can't be empty. Type can be UNKNOWN (10) (see more in include/tree/element.h)
// name can be empty.
double		nfAddElementInSegment(const char *name, const char *content, int type)
{
  element	*new;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (strcmp(content, "") == 0)
    return (-1); // Verify error code
  // if type is outside of the attr type enumeration.
  if (type > 10 || type < 0)
    return (-1); // Verify error code.
  // If malloc failed
  if (!(new = malloc(sizeof(*new))))
    return (-1); // Verify Error Code
  new->id = lastElementID(g_msg->segment->element) + 1;
  if (strcmp(name, "") != 0)
    new->name = strdup(name);
  else
    new->name = NULL;
  new->content = strdup(content);
  new->type = (enum e_attr_type)type;
  addElement(&(g_msg->segment->element), new);
  return (0);
}

// Add an element at the end of the list of the pointed element inside the pointed child.
// If the pointed element is NULL (understand that there is no element)
// The element will create a new element list on the pointed segment.
// new_id is important. If its value is 0, it will be automatically setted to the last ID available.
// If its value is already in the list of element, it will be modifyed and will receive an available ID.
// Content can't be empty. Type can be UNKNOWN (10) (see more in include/tree/element.h)
// name can be empty.
double		nfAddElementInChild(const char *name, const char *content, int type)
{
  element	*new;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL)
    return (-1);
  if (strcmp(content, "") == 0)
    return (-1); // Verify error code
  // if type is outside of the attr type enumeration.
  if (type > 10 || type < 0)
    return (-1); // Verify error code.
  // If malloc failed
  if (!(new = malloc(sizeof(*new))))
    return (-1); // Verify Error Code
  new->id = lastElementID(g_msg->segment->child->element) + 1;
  if (strcmp(name, "") != 0)
    new->name = strdup(name);
  else
    new->name = NULL;
  new->content = strdup(content);
  new->type = (enum e_attr_type)type;
  addElement(&(g_msg->segment->child->element), new);
  return (0);
}

// Add an element in the specifyed segment by its od
double		nfAddElementInSegmentID(int id, int new_id, const char *name, const char *content, int type)
{
  int		error_code;
  int		last_pos;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  last_pos = g_msg->segment->id;
  if ((error_code = nfGoToIDSegment(id)) != 0)
    return (error_code);
  if ((error_code = nfAddElementInSegment(name, content, type)) != 0)
    {
      nfGoToIDSegment(last_pos);
      return (error_code);
    }
  g_msg->segment->element->id = new_id;
  return (0);
}

// Add an element in the specifyed Segment by its name
double		nfAddElementInSegmentName(const char *name, const char *new_name, \
					  const char *content, int type)
{
  int		error_code;
  char		*last_pos_name;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  last_pos_name = g_msg->segment->name;
  if ((error_code = nfGoToNameSegment(name)) != 0)
    return (error_code);
  if ((error_code = nfAddElementInSegment(new_name, content, type)) != 0)
    {
      nfGoToNameSegment(last_pos_name);
      return (error_code);
    }
  return (0);
}

// Add an element in the specified child by its id
double		nfAddElementInChildID(int id, int new_id, const char *name, const char *content, int type)
{
  int		error_code;
  int		last_pos;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL)
    return (-1);
  last_pos = g_msg->segment->child->id;
  if ((error_code = nfGoToIDChild(id)) != 0)
    return (error_code);
  if ((error_code = nfAddElementInChild(name, content, type)) != 0)
    {
      nfGoToIDChild(last_pos);
      return (error_code);
    }
  g_msg->segment->child->element->id = new_id;
  return (0);
}

// Add an element in the specified child by its name
double		nfAddElementInChildName(const char *name, const char *new_name, \
					const char *content, int type)
{
  int		error_code;
  char		*last_pos_name;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL)
    return (-1);
  last_pos_name = g_msg->segment->child->name;
  if ((error_code = nfGoToNameChild(name)) != 0)
    return (error_code);
  if ((error_code = nfAddElementInChild(new_name, content, type)) != 0)
    {
      nfGoToNameChild(last_pos_name);
      return (error_code);
    }
  return (0);  
}

// Add an element of type numeric. the value is converted in string.
double		nfAddNumeric(const char *name, int value)
{
  char		*int_converted;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  int_converted = int_to_string(value);
  if (!newElement(&(g_msg->segment->element), name, lastElementID(g_msg->segment->element) + 1, int_converted, NUM))
    return (-1);
  free(int_converted);
  return (0);
}

// Add an element of type string.
double		nfAddString(const char *name, const char *value)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (!newElement(&(g_msg->segment->element), name, lastElementID(g_msg->segment->element) + 1, value, STRING))
    return (-1);
  return (0);
}

// Add an element of type NULL OBJECT. No need of value because it will be "NULL" in any case
double		nfAddNullObject(const char *name)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (!newElement(&(g_msg->segment->element), name, lastElementID(g_msg->segment->element) + 1, "null", NULLOBJ))
    return (-1);
  return (0);
}

// Add an element of type boolean. The value is either TRUE (1) or FALSE (0).
double		nfAddBoolean(const char *name, int boolean)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (boolean == 1)
    {
      if (!newElement(&(g_msg->segment->element), name,			\
		      lastElementID(g_msg->segment->element) + 1, "true", BOOL))
	return (-1);
      return (0);
    }
  if (boolean == 0)
    {
      if (!newElement(&(g_msg->segment->element), name,			\
		      lastElementID(g_msg->segment->element) + 1, "false", BOOL))
	return (-1);
      return (0);
    }
  return (-1);
}

// Add an element of type Date. THe format of the date must be : dd-mm-yyyy
// dd : Digit for the day.
// mm : digit for the month.
// yy : Full year.
double		nfAddDate(const char *name, const char *date)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (!newElement(&(g_msg->segment->element), name, lastElementID(g_msg->segment->element) + 1, date, DATE))
    return (-1);
  return (0);
}

// Add an element of type time. The format of the time must be : hh:mm:ss
// hh : Digit for hours.
// mm : digit for minutes.
// ss : digit for seconds.
double		nfAddTime(const char *name, const char *time)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (!newElement(&(g_msg->segment->element), name, lastElementID(g_msg->segment->element) + 1, time, TIME))
    return (-1);
  return (0);
}

#endif		/* __MODIFY_ELEMENT_C__ */
