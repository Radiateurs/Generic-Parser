#ifndef		__MODIFY_SEGMENT_C__
# define	__MODIFY_SEGMENT_C__

# include	"generic_parser.h"
# include	"navigation/movement.h"

// V.0.1 Low level verification
// TODO : Error code + ID verification
double		nfDeleteIDSegment(int id)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (deleteIDSegment(&(g_msg->segment), id) == 0)
    return (-1);
  return (0);
}

double		nfDeleteNameSegment(const char *name)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if ((error_return = nfGoToNameSegment(name)) != 0)
    return (error_return);
  if (deleteIDSegment(&(g_msg->segment), g_msg->segment->id) == 0)
    return (-1);
  return (0);
}

// Delete the pointed segment and move to the parent of it.
double		nfDeleteSegment()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if (deleteIDSegment(&(g_msg->segment), g_msg->segment->id) == 0)
    return (-1);
  return (0);
}

// Delete the list of the pointed segment and move to the parent of it.
double		nfDeleteAllSegment()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if (deleteListSegments(&(g_msg->segment)) != 0)
    return (-1);
  return (0);
}

double		nfModifyIDSegmentName(int id, const char *new_name)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if ((error_return = nfGoToIDSegment(id)) != 0)
    return (error_return);
  free(g_msg->segment->name);
  g_msg->segment->name = strdup(new_name);
  return (0);
}

double		nfModifyNameSegmentName(const char *name, const char *new_name)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if ((error_return = nfGoToNameSegment(name)) != 0)
    return (error_return);
  free(g_msg->segment->name);
  g_msg->segment->name = strdup(new_name);
  return (0);
}

double		nfModifySegmentName(const char *new_name)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  free(g_msg->segment->name);
  g_msg->segment->name = strdup(new_name);
  return (0);
}

double		nfModifyIDSegmentID(int id, int new_id)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if ((error_return = nfGoToIDSegment(id)) != 0)
    return (error_return);
  g_msg->segment->id = new_id;
  return (0);
}

double		nfModifyNameSegmentID(const char *name, int new_id)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if ((error_return = nfGoToNameSegment(name)) != 0)
    return (error_return);
  g_msg->segment->id = new_id;
  return (0);
}

// Modify the pointed segment's ID by new_id
double		nfModifySegmentID(int new_id)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  g_msg->segment->id = new_id;
  return (0);
}

double		nfModifyNameSegmentType(const char *name, int new_type)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if ((error_return = nfGoToNameSegment(name)) != 0)
    return (error_return);
  g_msg->segment->type = new_type;
  return (0);
}

// Modify the pointed segment's ID by new_id
double		nfModifySegmentType(int new_type)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  g_msg->segment->id = new_type;
  return (0);
}

// Add a segment at the end of list of the pointed / ID / Name segment.
double		nfAddSegment(const char *name)
{
  segment	*new;
  int		real_id;

  if (g_msg == NULL)
    return (-1);
  real_id = lastSegmentID(g_msg->segment) + 1;
  if (!(new = initSegment(name, real_id, 1, ((g_msg->segment == NULL) ? 0 : g_msg->segment->depth), 0)))
    return (-1); // Verify error code
  if (addSegment(&(g_msg->segment), new, 0) != 1)
    return (-1); // Verify error code
  return (0);
}

double		nfAddList(const char *name)
{
  segment	*new;

  if (!(new = initSegment(name, lastSegmentID(g_msg->segment) + 1, 1,	\
			  ((g_msg->segment == NULL) ? 0 : g_msg->segment->depth), SLIST)))
    return (-1);
  if (addSegment(&(g_msg->segment), new, 0) != 1)
    return (-1);
  return (0);
}

double		nfAddTab(const char *name)
{
  segment	*new;

  if (!(new = initSegment(name, lastSegmentID(g_msg->segment) + 1, 1,	\
			  ((g_msg->segment == NULL) ? 0 : g_msg->segment->depth), STAB)))
    return (-1);
  if (addSegment(&(g_msg->segment), new, 0) != 1)
    return (-1);
  return (0);
}

#endif		/* __MODIFY_SEGMENT_C__ */
