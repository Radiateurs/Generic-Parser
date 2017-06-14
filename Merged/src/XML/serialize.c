#ifndef		__XML_SERIALIZE_C__
# define	__XML_SERIALIZE_C__

# include	"XMLParser.h"
# include	<stdio.h>

/*
** Dump just one Element(understand attribut) with its content
*/
void		XMLDumpElement(int fd, element *elem, int realDepth)
{
  int		depth = 0;
  int		nb_tab = 0;
  
  if (elem == NULL)
    return ;
  // If the element name contain a g_text char at first place (# by default) it will be printed
  // as a text and not as an attribut of the tag
  if (elem->name[0] == g_text)
    {
      dprintf(fd, ">");
      if (g_human_readable == 1)
	dprintf(fd, "%s", CRLF);
      // If the human_readable mode has been activated by the user,
      // This will indent the datas in the file
      while (g_human_readable == 1 && depth < realDepth)
	{
	  nb_tab = 0;
	  while (nb_tab < g_nb_spacer)
	    {
	      dprintf(fd, "%c", g_spacer);
	      nb_tab++;
	    }
	  depth++;
	}
      dprintf(fd, "%s", elem->content);
      if (g_human_readable == 1)
	dprintf(fd, "%s", CRLF);
    }
  else
    dprintf(fd, " %s=\"%s\"", (elem->name[0] == g_attribut) ? elem->name + 1 : elem->name,
	    (elem->content == NULL) ? "" : elem->content);
}

/*
** Dump all the element(understand attribut of the tag)
*/
void		XMLDumpAllElement(int fd, element *elem, int depth)
{
  element	*tmp;
  element	*value;

  if (elem == NULL)
    return ;
  value = NULL;
  tmp = elem;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp)
    {
      // Skip the pointed element because it has to by printed in last
      // It's saved by the variable 'value'
      if (tmp->name[0] == g_text)
	{
	  value = tmp;
	  tmp = tmp->next;
	  continue ;
	}
      XMLDumpElement(fd, tmp, depth);
      if (tmp->next == NULL)
	break ;
      tmp = tmp->next;
    }
  if (value != NULL)
    XMLDumpElement(fd, value, depth);
}

/*
** Dump the segment name and the indentation if needed
*/
void		XMLDumpOpeningSegment(int fd, segment *seg)
{
  int		depth = 0;
  int		nb_tab = 0;

  while (g_human_readable == 1 && depth < seg->depth)
    {
      nb_tab = 0;
      while (nb_tab < g_nb_spacer)
	{
	  dprintf(fd, "%c", g_spacer);
	  nb_tab++;
	}
      depth++;
    }
  /*
  ** The following if forest is made to print the opening segment's name (tag) 
  ** depending on the available variable.
  ** 1 - If no name and the segment is the first one (root) dump the tag as '<root>'
  ** 2 - If has a name dump it simply
  ** 3 - If no name but the parent has one and it's a tab (suggest that the current child is a list),
  **     dump the parent name.
  ** 4 - If no name and the parent neither and the parent is a tab, dump '<element[id]'.
  **     [id] being the actual segment's id.
  */
  if (seg->name == NULL && seg->parent == NULL)
    dprintf(fd, "<root");
  if (seg->name != NULL)
    dprintf(fd, "<%s", seg->name);
  if (seg->name == NULL && seg->parent != NULL &&		\
      seg->parent->name != NULL && seg->parent->type == STAB)
    dprintf(fd, "<%s", seg->parent->name);
  if (seg->name == NULL && seg->parent != NULL && seg->parent->name == NULL && seg->parent->type == STAB)
    dprintf(fd, "<element%i", seg->id);
}

/*
** Dump the end of a segment (closing tag) and indentation if needed
*/
void		XMLDumpClosingSegment(int fd, segment *seg)
{
  int		depth = 0;
  int		nb_tab = 0;

  // When the pointed segment do not contains childs and has no text element, dump the end of the tag has '/>'
  if (seg->child == NULL && segmentHasNoText(seg) == 1)
    {
      dprintf(fd, "/>");
      if (g_human_readable == 1)
	dprintf(fd, "%s", CRLF);
      return ;
    }
  while (g_human_readable == 1 && depth < seg->depth)
    {
      nb_tab = 0;
      while (nb_tab < g_nb_spacer)
	{
	  dprintf(fd, "%c", g_spacer);
	  nb_tab++;
	}
      depth++;
    }
  /*
  ** The following if forest is made to print the closing segment's name (tag) 
  ** depending on the available variable.
  ** 1 - If no name and the segment is the first one (root) dump the tag as '</root>'
  ** 2 - If has a name dump it simply
  ** 3 - If no name but the parent has one and it's a tab (suggest that the current child is a list),
  **     dump the parent name.
  ** 4 - If no name and the parent neither and the parent is a tab, dump '</element[id]'.
  **     [id] being the actual segment's id.
  */
  if (seg->name == NULL && seg->parent == NULL)
    dprintf(fd, "</root>");
  if (seg->name != NULL)
    dprintf(fd, "</%s>", seg->name);
  if (seg->name == NULL && seg->parent != NULL &&		\
      seg->parent->name != NULL && seg->parent->type == STAB)
    dprintf(fd, "</%s>", seg->parent->name);
  if (seg->name == NULL && seg->parent != NULL && seg->parent->name == NULL && seg->parent->type == STAB)
    dprintf(fd, "</element%i>", seg->id);
  if (g_human_readable == 1)
    dprintf(fd, "%s", CRLF);
}

/*
** Calls function to dump the pointed segment
*/
void		XMLDumpSegment(int fd, segment *seg)
{
  if (seg == NULL)
    return ;
  // As the segment is a tab and it's not the root, it shouldn't dump its name
  // beacause of the multiplicity of childs
  if (seg->type == STAB && seg->parent != NULL)
    {
      XMLDumpAllSegment(fd, seg->child);
      return ;
    }
  XMLDumpOpeningSegment(fd, seg);
  if (seg->type != STAB)
    XMLDumpAllElement(fd, seg->element, seg->depth + 1);
  if (seg->child != NULL && segmentHasNoText(seg) == 1)
    {
      dprintf(fd, ">");
      if (g_human_readable == 1)
	dprintf(fd, "%s", CRLF);
    }
  XMLDumpAllSegment(fd, seg->child);
  XMLDumpClosingSegment(fd, seg);
}

/*
** Navigate trought the segments one by one to dump them
*/
void		XMLDumpAllSegment(int fd, segment *seg)
{
  segment	*tmp;

  if (seg == NULL)
    return ;
  tmp = seg;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp)
    {
      XMLDumpSegment(fd, tmp);
      if (tmp->next == NULL)
	return ;
      tmp = tmp->next;
    }
}

/*
** Go to the first segment node and dump all ones by hierarchical order in fd.
*/
void		XMLwriting(int fd, message *msg)
{
  while (msg != NULL && msg->segment != NULL && msg->segment->parent != NULL)
    msg->segment = msg->segment->parent;
  while (msg != NULL && msg->segment != NULL && msg->segment->prev != NULL)
    msg->segment = msg->segment->prev;
  XMLDumpAllSegment(fd, msg->segment);
}

#endif		/* __XML_SERIALIZE_C__ */
