#ifndef		__MODIFY_CHILD_C__
# define	__MODIFY_CHILD_C__

# include	"generic_parser.h"
# include	"navigation/movement.h"

double		nfDeleteIDChild(int id)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (deleteIDSegment(&(g_msg->segment->child), id) == 0)
    return (-1);
  return (0);
}

double		nfDeleteNameChild(const char *name)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if ((error_return = nfGoToNameChild(name)) != 0)
    return (error_return);
  if (deleteIDSegment(&(g_msg->segment->child), g_msg->segment->child->id) == 0)
    return (-1);
  return (0);
}

// Delete the pointed segment's child.
double		nfDeleteChild()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if (deleteIDSegment(&(g_msg->segment->child), g_msg->segment->child->id) == 0)
    return (-1);
  return (0);
}

// Delete the list of the pointed segment and move to the parent of it.
double		nfDeleteAllChild()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if (deleteListSegments(&(g_msg->segment->child)) == 0)
    return (-1);
  g_msg->segment->child = NULL;
  return (0);  
}

double		nfModifyIDChildName(int id, const char *new_name)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if ((error_return = nfGoToIDChild(id)) != 0)
    return (error_return);
  free(g_msg->segment->child->name);
  g_msg->segment->child->name = strdup(new_name);
  return (0);
}

double		nfModifyNameChildName(const char *name, const char *new_name)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if ((error_return = nfGoToNameChild(name)) != 0)
    return (error_return);
  free(g_msg->segment->child->name);
  g_msg->segment->child->name = strdup(new_name);
  return (0);
}

double		nfModifyChildName(const char *new_name)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  free(g_msg->segment->child->name);
  g_msg->segment->child->name = strdup(new_name);
  return (0);
}

double		nfModifyIDChildID(int id, int new_id)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if ((error_return = nfGoToIDChild(id)) != 0)
    return (error_return);
  g_msg->segment->child->id = new_id;
  return (0);
}

double		nfModifyNameChildID(const char *name, int new_id)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if ((error_return = nfGoToNameChild(name)) != 0)
    return (error_return);
  g_msg->segment->child->id = new_id;
  return (0);
}

// Modify the pointed segment's ID by new_id
double		nfModifyChildID(int new_id)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  g_msg->segment->child->id = new_id;
  return (0);
}

// Add a segment (child) at the end of list of the pointed / ID / Name segment.
double		nfAddChildInSegment(int new_id, const char *name)
{
  segment	*new;
  int		real_id;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (new_id == 0 || getIDSegment(g_msg->segment->child, new_id) != NULL ||
      getIDElement(g_msg->segment->element, new_id) != NULL)
    real_id = getNextID(g_msg->segment);
  else
    real_id = new_id;
  // If creation failed
  if (!(new = initSegment(name, real_id, 1, g_msg->segment->depth + 1, 0)))
    return (-1); //Verify error code
  if (addChild(&(g_msg->segment), new) != 1)
    return (-1); // Verify error code
  return (0);
}

double		nfAddChildInSegmentID(int id, int new_id, const char *new_name)
{
  int		error_code;
  int		last_pos_id;

  if (g_msg != NULL || g_msg->segment == NULL)
    return (-1);
  last_pos_id = g_msg->segment->id;
  if ((error_code = nfGoToIDSegment(id)) != 0)
    return (error_code);
  if ((error_code = nfAddChildInSegment(new_id, new_name)) != 0)
    {
      nfGoToIDSegment(last_pos_id);
      return (error_code);
    }
  return (0);
}

double		nfAddChildInSegmentName(const char *name, int new_id, const char *new_name)
{
  int		error_code;
  char		*last_pos_name;

  if (g_msg != NULL || g_msg->segment == NULL)
    return (-1);
  last_pos_name = g_msg->segment->name;
  if ((error_code = nfGoToNameSegment(name)) != 0)
    return (error_code);
  if ((error_code = nfAddChildInSegment(new_id, new_name)) != 0)
    {
      nfGoToNameSegment(last_pos_name);
      return (error_code);
    }
  return (0);
}

// Add a segment (child) at the end of list of the pointed / ID / Name child.
double		nfAddChildInChild(int new_id, const char *new_name)
{
  segment	*new;
  int		real_id;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL)
    return (-1);
  if (new_id == 0 || getIDSegment(g_msg->segment->child->child, new_id) != NULL ||
      getIDElement(g_msg->segment->child->element, new_id) != NULL)
    real_id = getNextID(g_msg->segment->child);
  else
    real_id = new_id;
  // If creation failed
  if (!(new = initSegment(new_name, real_id, 1, g_msg->segment->depth + 1, 0)))
    return (-1); //Verify error code
  if (addChild(&(g_msg->segment->child), new) != 1)
    return (-1); // Verify error code
  return (0);
}

double		nfAddChildInChildID(int id, int new_id, const char *new_name)
{
  int		error_code;
  int		last_pos_id;

  if (g_msg != NULL || g_msg->segment == NULL ||g_msg->segment->child)
    return (-1);
  last_pos_id = g_msg->segment->child->id;
  if ((error_code = nfGoToIDChild(id)) != 0)
    return (error_code);
  if ((error_code = nfAddChildInChild(new_id, new_name)) != 0)
    {
      nfGoToIDChild(last_pos_id);
      return (error_code);
    }
  return (0);
}

double		nfAddChildInChildName(const char *name, int new_id, const char *new_name)
{
  int		error_code;
  char		*last_pos_name;

  if (g_msg != NULL || g_msg->segment == NULL || g_msg->segment->child == NULL)
    return (-1);
  last_pos_name = g_msg->segment->child->name;
  if ((error_code = nfGoToNameChild(name)) != 0)
    return (error_code);
  if ((error_code = nfAddChildInChild(new_id, new_name)) != 0)
    {
      nfGoToNameChild(last_pos_name);
      return (error_code);
    }
  return (0);
}

#endif		/* __MODIFY_CHILD_C__ */
