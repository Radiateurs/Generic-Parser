#ifndef		__MODIFY_ELEMENT_C__
# define	__MODIFY_ELEMENT_C__

# include	"generic_parser.h"
# include	"navigation/movement.h"

// Delete the pointed element
int		nfDeleteElement()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if (deleteIDElement(&(g_msg->segment->element), g_msg->segment->element->id) == 0)
    return (-1); // Verify error code
  return (0);
}

int		nfDeleteAllElement()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if (deleteElements(&(g_msg->segment->element)) == 0)
    return (-1);
  return (0);
}

int		nfDeleteIDElement(int id)
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if (deleteIDElement(&(g_msg->segment->element), id) == 0)
    return (-1);
  return (0);
}

int		nfDeleteNameElement(const char *name)
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

int		nfModifyElement(int new_id, const char *new_name, const char *new_content)
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if (new_id > 0)
    g_msg->segment->element->id = new_id;
  if (new_name != NULL && strcmp(new_name, "") != 0)
    {
      free(g_msg->segment->element->name);
      g_msg->segment->element->name = strdup(new_name);
    }
  if (new_content != NULL && strcmp(new_content, "") != 0)
    {
      free(g_msg->segment->element->content);
      g_msg->segment->element->content = strdup(new_content);
    }
  return (0);
}

int		nfModifyElementID(int new_id)
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->element == NULL)
    return (-1);
  if (new_id > 0)
    g_msg->segment->element->id = new_id;
  return (0);
}

int		nfModifyIDElementID(int id, int new_id)
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

int		nfModifyNameElementID(const char *name, int new_id)
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

int		nfModifyElementName(const char *new_name)
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

int		nfModifyIDElementName(int id, const char *new_name)
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

int		nfModifyNameElementName(const char *name, const char *new_name)
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

int		nfModifyElementContent(const char *new_content, int type)
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

int		nfModifyIDElementContent(int id, const char *new_content, int type)
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

int		nfModifyNameElementContent(const char *name, const char *new_content, int type)
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
int		nfAddElementInSegment(int new_id, const char *name, const char *content, int type)
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
  if (new_id == 0 || getIDElement(g_msg->segment->element, new_id))
    new->id = lastElementID(g_msg->segment->element) + 1;
  else
    new->id = new_id;
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
int		nfAddElementInChild(int new_id, const char *name, const char *content, int type)
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
  if (new_id == 0 || getIDElement(g_msg->segment->child->element, new_id))
    new->id = lastElementID(g_msg->segment->child->element) + 1;
  else
    new->id = new_id;
  if (strcmp(name, "") != 0)
    new->name = strdup(name);
  else
    new->name = NULL;
  new->content = strdup(content);
  new->type = (enum e_attr_type)type;
  addElement(&(g_msg->segment->child->element), new);
  return (0);
}

int		nfAddElementInSegmentID(int id, int new_id, const char *name, const char *content, int type)
{
  int		error_code;
  int		last_pos;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  last_pos = g_msg->segment->id;
  if ((error_code = nfGoToIDSegment(id)) != 0)
    return (error_code);
  if ((error_code = nfAddElementInSegment(new_id, name, content, type)) != 0)
    {
      nfGoToIDSegment(last_pos);
      return (error_code);
    }
  return (0);
}

int		nfAddElementInSegmentName(const char *name, int new_id, const char *new_name, \
					  const char *content, int type)
{
  int		error_code;
  char		*last_pos_name;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  last_pos_name = g_msg->segment->name;
  if ((error_code = nfGoToNameSegment(name)) != 0)
    return (error_code);
  if ((error_code = nfAddElementInSegment(new_id, new_name, content, type)) != 0)
    {
      nfGoToNameSegment(last_pos_name);
      return (error_code);
    }
  return (0);
}

int		nfAddElementInChildID(int id, int new_id, const char *name, const char *content, int type)
{
  int		error_code;
  int		last_pos;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL)
    return (-1);
  last_pos = g_msg->segment->child->id;
  if ((error_code = nfGoToIDChild(id)) != 0)
    return (error_code);
  if ((error_code = nfAddElementInChild(new_id, name, content, type)) != 0)
    {
      nfGoToIDChild(last_pos);
      return (error_code);
    }
  return (0);
}

int		nfAddElementInChildName(const char *name , int new_id, const char *new_name, \
					const char *content, int type)
{
  int		error_code;
  char		*last_pos_name;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL)
    return (-1);
  last_pos_name = g_msg->segment->child->name;
  if ((error_code = nfGoToNameChild(name)) != 0)
    return (error_code);
  if ((error_code = nfAddElementInChild(new_id, new_name, content, type)) != 0)
    {
      nfGoToNameChild(last_pos_name);
      return (error_code);
    }
  return (0);  
}

#endif		/* __MODIFY_ELEMENT_C__ */
