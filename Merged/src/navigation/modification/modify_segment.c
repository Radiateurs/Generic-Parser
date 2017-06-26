#ifndef		__MODIFY_SEGMENT_C__
# define	__MODIFY_SEGMENT_C__

# include	"generic_parser.h"
# include	"navigation/movement.h"

// V.0.1 Low level verification
// TODO : Error code + ID verification
int		nfDeleteIDSegment(int id)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  if (deleteIDSegment(&(g_msg->segment), id) == 0)
    return (-1);
  return (0);
}

int		nfDeleteNameSegment(const char *name)
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
int		nfDeleteSegment()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if (deleteIDSegment(&(g_msg->segment), g_msg->segment->id) == 0)
    return (-1);
  return (0);
}

// Delete the list of the pointed segment and move to the parent of it.
int		nfDeleteAllSegment()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if (deleteListSegments(&(g_msg->segment)) != 0)
    return (-1);
  return (0);
}

int		nfModifyIDSegmentName(int id, const char *new_name)
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

int		nfModifyNameSegmentName(const char *name, const char *new_name)
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

int		nfModifySegmentName(const char *new_name)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  free(g_msg->segment->name);
  g_msg->segment->name = strdup(new_name);
  return (0);
}

int		nfModifyIDSegmentID(int id, int new_id)
{
  int		error_return;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  if ((error_return = nfGoToIDSegment(id)) != 0)
    return (error_return);
  g_msg->segment->id = new_id;
  return (0);
}

int		nfModifyNameSegmentID(const char *name, int new_id)
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
int		nfModifySegmentID(int new_id)
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1); // Verify error code
  g_msg->segment->id = new_id;
  return (0);
}

// Add a segment at the end of list of the pointed / ID / Name segment.
int		nfAddSegmentInSegment(int new_id, const char *name)
{
  segment	*new;
  int		real_id;

  if (g_msg == NULL)
    return (-1);
  if (new_id == 0 || getIDSegment(g_msg->segment, new_id) != NULL)
    real_id = lastSegmentID(g_msg->segment);
  else
    real_id = new_id;
  if (!(new = initSegment(name, real_id, 1, ((g_msg->segment == NULL) ? 0 : g_msg->segment->id), 0)))
    return (-1); // Verify error code
  if (addSegment(&(g_msg->segment), new, 0) != 1)
    return (-1); // Verify error code
  return (0);
}

int		nfAddSegmentInSegmentID(int id, int new_id, const char *name)
{
  int		error_code;
  int		last_pos_id;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  last_pos_id = g_msg->segment->id;
  if ((error_code = nfGoToIDSegment(id)) != 0)
    return (error_code);
  if ((error_code = nfAddSegmentInSegment(new_id, name)) != 0)
    {
      nfGoToIDSegment(last_pos_id);
      return (error_code);
    }
  return (0);
}

int		nfAddSegmentInSegmentName(const char *name, int new_id, const char *new_name)
{
  int		error_code;
  char		*last_pos_name;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  last_pos_name = g_msg->segment->name;
  if ((error_code = nfGoToNameSegment(name)) != 0)
    return (error_code);
  if ((error_code = nfAddSegmentInSegment(new_id, new_name)) != 0)
    {
      nfGoToNameSegment(last_pos_name);
      return (error_code);
    }
  return (0);
}

#endif		/* __MODIFY_SEGMENT_C__ */
