#ifndef		__ACCESS_SEGMENT_C__
# define	__ACCESS_SEGMENT_C__

# include	"generic_parser.h"
# include	"navigation/access.h"

// Return the root's name
char		*tfGetRootName()
{
  segment	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL)
    return ("");
  tmp = g_msg->segment;
  while (tmp->parent != NULL)
    tmp = tmp->parent;
  if (tmp->name == NULL)
    return ("");
  return (tmp->name);
}

// Return the pointed segement's parent's name.
char		*tfGetParentName()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->parent == NULL || \
      g_msg->segment->parent->name == NULL)
    return ("");
  return (g_msg->segment->parent->name);
}

// Return the pointed segment's parent's id.
double		nfGetParentID()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->parent == NULL)
    return (-1);
  return (g_msg->segment->parent->id);
}

// Return the pointed segment's name
char		*tfGetSegmentName()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->name == NULL)
    return ("");
  return (g_msg->segment->name);
}

// Return the next segment's name relative to the pointed segment
char		*tfGetNextSegmentName()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->next == NULL || \
      g_msg->segment->next->name == NULL)
    return ("");
  return (g_msg->segment->next->name);
}

// Return the previous segment's name relative to the pointed segment
char		*tfGetPreviousSegmentName()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->prev == NULL || \
      g_msg->segment->prev->name == NULL)
    return ("");
  return (g_msg->segment->next->name);
}

// Return the first segment's name relative to the pointed segment's list
char		*tfGetFirstSegmentName()
{
  segment	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL)
    return ("");
  tmp = g_msg->segment;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  if (tmp->name == NULL)
    return ("");
  return (tmp->name);
}

// Return the first segment's name relative to the pointed segment's list
char		*tfGetLastSegmentName()
{
  segment	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL)
    return ("");
  tmp = g_msg->segment;
  while (tmp->next != NULL)
    tmp = tmp->next;
  if (tmp->name == NULL)
    return ("");
  return (tmp->name);
}

// Return the pointed segment's id
double		nfGetSegmentID()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  return (g_msg->segment->id);
}

// Return the next segment's id on the pointed segment
double		nfGetNextSegmentID()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->next == NULL)
    return (-1);
  return (g_msg->segment->next->id);
}

// Return the previous segment's id on the pointed segment
double		nfGetPreviousSegmentID()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->prev == NULL)
    return (-1);
  return (g_msg->segment->prev->id);
}

// Return the first segment's id on the pointed segment
double		nfGetFirstSegmentID()
{
  segment	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  tmp = g_msg->segment;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  return (tmp->id);
}

// Return the last segment's id on the pointed segment
double		nfGetLastSegmentID()
{
  segment	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  tmp = g_msg->segment;
  while (tmp->next != NULL)
    tmp = tmp->next;
  return (tmp->id);
}

// Return the pointed segment's depth
double		nfGetSegmentDepth()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  return (g_msg->segment->depth);
}

// Return the next segment's depth on the pointed segment
double		nfGetNextSegmentDepth()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->next == NULL)
    return (-1);
  return (g_msg->segment->next->depth);
}

// Return the previous segment's depth on the pointed segment
double		nfGetPreviousSegmentDepth()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->prev == NULL)
    return (-1);
  return (g_msg->segment->prev->depth);
}

// Return the first segment's depth on the pointed segment
double		nfGetFirstSegmentDepth()
{
  segment	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  tmp = g_msg->segment;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  return (tmp->depth);
}

// Return the last segment's depth on the pointed segment
double		nfGetLastSegmentDepth()
{
  segment	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  tmp = g_msg->segment;
  while (tmp->next != NULL)
    tmp = tmp->next;
  return (tmp->depth);
}

// Return the pointed segment's type
double		nfGetSegmentType()
{
  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  return (g_msg->segment->type);
}

// Return the next segment's type on the pointed segment
double		nfGetNextSegmentType()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->next == NULL)
    return (-1);
  return (g_msg->segment->next->type);
}

// Return the previous segment's type on the pointed segment
double		nfGetPreviousSegmentType()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->prev == NULL)
    return (-1);
  return (g_msg->segment->prev->type);
}

// Return the first segment's type on the pointed segment
double		nfGetFirstSegmentType()
{
  segment	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  tmp = g_msg->segment;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  return (tmp->type);
}

// Return the last segment's type on the pointed segment
double		nfGetLastSegmentType()
{
  segment	*tmp;

  if (g_msg == NULL || g_msg->segment == NULL)
    return (-1);
  tmp = g_msg->segment;
  while (tmp->next != NULL)
    tmp = tmp->next;
  return (tmp->type);
}

double		bfIsSegmentSeg()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->type != SSEG)
    return (0);
  return (1);
}

double		bfIsSegmentTab()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->type != STAB)
    return (0);
  return (1);
}

double		bfIsSegmentList()
{
  if (g_msg == NULL || g_msg->segment == NULL || g_msg->segment->type != SLIST)
    return (0);
  return (1);
}

#endif		/* __ACCESS_SEGMENT_C__ */
