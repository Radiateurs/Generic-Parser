#ifndef		__JSON_SERIALIZE_C__
# define	__JSON_SERIALIZE_C__

# include	"JSONParser.h"
# include	<stdio.h>

/*
** Serialize an Element in JSON
*/
void		JSONDumpElement(int fd, element *elem, int seg_depth)
{
  int		depth = 0;
  int		nb_of_tab;

  while (g_human_readable == 1 && depth < seg_depth)
    {
      nb_of_tab = 0;
      while (nb_of_tab <  g_nb_spacer)
	{
	  dprintf(fd, "%c", g_spacer);
	  nb_of_tab++;
	}
      depth++;
    }
  if (elem == NULL)
    return ;
  if (elem->name != NULL) // If an element doesn't have a name, it's obviously in a tab.
    dprintf(fd, "\"%s\":", elem->name);
  if (elem->type == ALPHA || elem->type == STRING || elem->type == ALNUM)
    dprintf(fd, "\"%s\"", elem->content);
  else
    dprintf(fd, "%s", elem->content);
}

/*
** Serialize the element's list in JSON
*/
void		JSONDumpAllElement(int fd, element *elem, int seg_depth)
{
  element	*tmp;

  if (elem == NULL)
    return ;
  tmp = elem;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp)
    {
      JSONDumpElement(fd, tmp, seg_depth);
      if (tmp->next == NULL)
	return ;
      dprintf(fd, ",");
      if (g_human_readable == 1)
	dprintf(fd, "%s", CRLF);
      tmp = tmp->next;
    }
}

/*
** Serialize a segment in JSON
*/
void		JSONDumpSegment(int fd, segment *seg) // Will dump only the pointed segment
{
  int		depth = 0;
  int		nb_of_tab;
  segment	*seg_in_tab;
  element	*elem_in_tab;
  unsigned int	current_id, max_id;

  if (seg == NULL)
    return ;
  // print indentation
  while (g_human_readable == 1 && depth < seg->depth)
    {
      nb_of_tab = 0;
      while (nb_of_tab <  g_nb_spacer)
	{
	  dprintf(fd, "%c", g_spacer);
	  nb_of_tab++;
	}
      depth++;
    }
  if (seg->name != NULL)
    dprintf(fd, "\"%s\":", seg->name);
  if (seg->type == SLIST) // Serialize all the element in passing order. And then its child
    {
      dprintf(fd, "{");
      if (g_human_readable == 1)
	dprintf(fd, "%s", CRLF);
      JSONDumpAllElement(fd, seg->element, seg->depth + 1);
      if (seg->child != NULL && seg->element != NULL)
	dprintf(fd, ",");
      if (seg->element != NULL && g_human_readable == 1)
	dprintf(fd, "%s", CRLF);
      JSONDumpAllSegment(fd, seg->child);
    }
  if (seg->type == STAB) // Serialize every Element in ID's order
    {
      dprintf(fd, "[");
      if (g_human_readable == 1)
	dprintf(fd, "%s", CRLF);
      // Get All the ID and print it by id order
      current_id = 1;
      max_id = countSegment(seg->child) + countElement(seg->element) + 1;
      while (current_id != max_id)
	{
	  // If ID is found as an element, print it
	  if ((elem_in_tab = getIDElement(seg->element, current_id)) != NULL)
	    JSONDumpElement(fd, elem_in_tab, seg->depth + 1);
	  // If ID is found as a segment, print it
	  else if ((seg_in_tab = getIDSegment(seg->child, current_id)) != NULL)
	    JSONDumpSegment(fd, seg_in_tab);
	  current_id++;
	  if (current_id != max_id)
	    dprintf(fd, ",");
	  if (g_human_readable == 1)
	    dprintf(fd, "%s", CRLF);
	}
    }
  // print indentation
  depth = 0;
  while (g_human_readable == 1 && depth < seg->depth)
    {
      nb_of_tab = 0;
      while (nb_of_tab <  g_nb_spacer)
	{
	  dprintf(fd, "%c", g_spacer);
	  nb_of_tab++;
	}
      depth++;
    }
  dprintf(fd, "%c", (seg->type == STAB) ? ']' : '}');
}

/*
** Serialize the segment's list
*/
void		JSONDumpAllSegment(int fd, segment *seg) // Will dump all element and child in the current segment
{
  segment	*tmp;

  if (seg == NULL)
    return ;
  tmp = seg;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp)
    {
      JSONDumpSegment(fd, tmp);
      if (tmp->next == NULL)
	{
	  if (g_human_readable == 1)
	    dprintf(fd, "%s", CRLF);
	  return ;
	}
      tmp = tmp->next;
      dprintf(fd, ",");
      if (g_human_readable == 1)
	dprintf(fd, "%s", CRLF);
    }
}

/*
** Serialize the message.
*/
void		JSONwriting(int fd, message *msg)
{
  if (msg == NULL)
    return ;
  while (msg != NULL && msg->segment != NULL && msg->segment->parent != NULL)
    msg->segment = msg->segment->parent;
  while (msg != NULL && msg->segment != NULL && msg->segment->prev != NULL)
    msg->segment = msg->segment->prev;
  JSONDumpAllSegment(fd, msg->segment);
}

#endif		/* __JSON_SERIALIZE_C__ */
