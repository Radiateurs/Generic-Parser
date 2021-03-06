#ifndef		__MODIFY_CHILD_C__
# define	__MODIFY_CHILD_C__

# include	"generic_parser.h"
# include	"navigation/movement.h"

// Delete the specidyed id child.
double		nfDeleteIDChild(int id)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (deleteIDSegment(&(g_msg->segment->child), id) == 0)
    return (-1);
  return (0);
}

// Delete the specifyed name child
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

// Modify the name of the specifyed id child
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

// Modify the name of the specifyed name child
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

// Modify the id of the specifyed id child
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

// Modify the name of the child
double		nfModifyChildName(const char *new_name)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  free(g_msg->segment->child->name);
  g_msg->segment->child->name = strdup(new_name);
  return (0);
}

// Modify the id of the specifyed name child
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

// Modify the type of the specifyed name child
double		nfModifyNameChildType(const char *name, int new_type)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if ((error_return = nfGoToNameChild(name)) != 0)
    return (error_return);
  g_msg->segment->child->type = new_type;
  return (0);
}

// Modify the pointed segment's ID by new_id
double		nfModifyChildType(int new_type)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  g_msg->segment->child->type = new_type;
  return (0);
}

// Add a segment (child) at the end of list of the pointed / ID / Name segment.
double		nfAddChildInSegment(const char *name)
{
  segment	*new;
  int		real_id;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  real_id = getNextID(g_msg->segment->child);
  // If creation failed
  if (!(new = initSegment(name, real_id, 1, g_msg->segment->depth + 1, 0)))
    return (-1); //Verify error code
  if (addChild(&(g_msg->segment), new) != 1)
    return (-1); // Verify error code
  return (0);
}

// Add a child in the specifyed segment id
double		nfAddChildInSegmentID(int id, const char *new_name)
{
  int		error_code;
  int		last_pos_id;

  if (g_msg != NULL || g_msg->segment == NULL)
    return (-1);
  last_pos_id = g_msg->segment->id;
  if ((error_code = nfGoToIDSegment(id)) != 0)
    return (error_code);
  if ((error_code = nfAddChildInSegment(new_name)) != 0)
    {
      nfGoToIDSegment(last_pos_id);
      return (error_code);
    }
  return (0);
}
 
/*
** Add a child in the first segment that has the same name as requested.
*/
double		nfAddChildInSegmentName(const char *name, const char *new_name)
{
  int		error_code;
  char		*last_pos_name;

  if (g_msg != NULL || g_msg->segment == NULL)
    return (-1);
  last_pos_name = g_msg->segment->name;
  if ((error_code = nfGoToNameSegment(name)) != 0)
    return (error_code);
  if ((error_code = nfAddChildInSegment(new_name)) != 0)
    {
      nfGoToNameSegment(last_pos_name);
      return (error_code);
    }
  return (0);
}

// Add a segment (child) at the end of list of the pointed / ID / Name child.
double		nfAddChildInChild(const char *new_name)
{
  segment	*new;
  int		real_id;

  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->child == NULL)
    return (-1);
  real_id = getNextID(g_msg->segment->child->child);
  // If creation failed
  if (!(new = initSegment(new_name, real_id, 1, g_msg->segment->depth + 1, 0)))
    return (-1); //Verify error code
  if (addChild(&(g_msg->segment->child), new) != 1)
    return (-1); // Verify error code
  return (0);
}

// Add a child in the specifyed id child
double		nfAddChildInChildID(int id, const char *new_name)
{
  int		error_code;
  int		last_pos_id;

  if (g_msg != NULL || g_msg->segment == NULL ||g_msg->segment->child)
    return (-1);
  last_pos_id = g_msg->segment->child->id;
  if ((error_code = nfGoToIDChild(id)) != 0)
    return (error_code);
  if ((error_code = nfAddChildInChild(new_name)) != 0)
    {
      nfGoToIDChild(last_pos_id);
      return (error_code);
    }
  return (0);
}

// Add a child in the specifyed name child
double		nfAddChildInChildName(const char *name, const char *new_name)
{
  int		error_code;
  char		*last_pos_name;

  if (g_msg != NULL || g_msg->segment == NULL || g_msg->segment->child == NULL)
    return (-1);
  last_pos_name = g_msg->segment->child->name;
  if ((error_code = nfGoToNameChild(name)) != 0)
    return (error_code);
  if ((error_code = nfAddChildInChild(new_name)) != 0)
    {
      nfGoToNameChild(last_pos_name);
      return (error_code);
    }
  return (0);
}

// Add a child in the first encountered list
double		nfAddChildList(const char *name)
{
  segment	*new;

  if (!(new = initSegment(name, lastSegmentID(g_msg->segment) + 1, 1,	\
			  ((g_msg->segment == NULL) ? 0 : g_msg->segment->depth), SLIST)))
    return (-1);
  if (addSegment(&(g_msg->segment), new, 1) != 1)
    return (-1);
  return (0);
}

// Add a child in the first encountered tab
double		nfAddChildTab(const char *name)
{
  segment	*new;

  if (!(new = initSegment(name, lastSegmentID(g_msg->segment) + 1, 1,	\
			  ((g_msg->segment == NULL) ? 0 : g_msg->segment->depth), STAB)))
    return (-1);
  if (addSegment(&(g_msg->segment), new, 1) != 1)
    return (-1);
  return (0);
}

/*
** Add a child Tab in the first segment that has the same name as requested.
*/
double		nfAddChildTabInSegmentName(const char *name, const char *new_name)
{
  int		error_code;
  char		*last_pos_name;

  if (g_msg != NULL || g_msg->segment == NULL)
    return (-1);
  last_pos_name = g_msg->segment->name;
  if ((error_code = nfGoToNameSegment(name)) != 0)
    return (error_code);
  if ((error_code = nfAddChildTab(new_name)) != 0)
    {
      nfGoToNameSegment(last_pos_name);
      return (error_code);
    }
  return (0);
}

/*
** Add a child in the first segment that has the same name as requested.
*/
double		nfAddChildListInSegmentName(const char *name, const char *new_name)
{
  int		error_code;
  char		*last_pos_name;

  if (g_msg != NULL || g_msg->segment == NULL)
    return (-1);
  last_pos_name = g_msg->segment->name;
  if ((error_code = nfGoToNameSegment(name)) != 0)
    return (error_code);
  if ((error_code = nfAddChildList(new_name)) != 0)
    {
      nfGoToNameSegment(last_pos_name);
      return (error_code);
    }
  return (0);
}


#endif		/* __MODIFY_CHILD_C__ */
