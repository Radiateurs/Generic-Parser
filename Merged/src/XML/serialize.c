#include	"XMLParser.h"
#include	<stdio.h>

void		XMLDumpAttribut(int fd, attribut *attr, int elem_depth)
{
  int		depth = 0;
  int		nb_tab = 0;

  if (attr == NULL)
    return ;
  while (g_human_readable == 1 && depth < elem_depth)
    {
      nb_tab = 0;
      while (nb_tab < g_nb_spacer)
	{
	  dprintf(fd, "\t");
	  nb_tab++;
	}
      depth++;
    }
  dprintf(fd, "%s", attr->content);
  if (g_human_readable == 1)
    dprintf(fd, "\n");
}

void		XMLDumpOpeningElement(int fd, element *elem, int seg_depth)
{
  int		depth = 0;
  int		nb_tab = 0;

  if (elem == NULL)
    return ;
  while (g_human_readable == 1 && depth < seg_depth)
    {
      nb_tab = 0;
      while (nb_tab < g_nb_spacer)
	{
	  dprintf(fd, "\t");
	  nb_tab++;
	}
      depth++;
    }
  if (elem != NULL && elem->name != NULL)
    dprintf(fd, "<%s>", elem->name);
  if (g_human_readable == 1)
    dprintf(fd, "\n");
}

void		XMLDumpClosingElement(int fd, element *elem, int seg_depth)
{
  int		depth = 0;
  int		nb_tab = 0;

  if (elem == NULL)
    return ;
  while (g_human_readable == 1 && depth < seg_depth)
    {
      nb_tab = 0;
      while (nb_tab < g_nb_spacer)
	{
	  dprintf(fd, "\t");
	  nb_tab++;
	}
      depth++;
    }
  if (elem->name != NULL)
    dprintf(fd, "</%s>", elem->name);
  if (g_human_readable == 1)
    dprintf(fd, "\n");
}


void		XMLDumpElement(int fd, element *elem, int depth)
{
  if (elem == NULL)
    return ;
  XMLDumpOpeningElement(fd, elem, depth);
  XMLDumpAttribut(fd, elem->attribut, depth + 1);
  XMLDumpClosingElement(fd, elem, depth);
}

void		XMLDumpAllElement(int fd, element *elem, int depth)
{
  element	*tmp;

  if (elem == NULL)
    return ;
  tmp = elem;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp)
    {
      XMLDumpElement(fd, tmp, depth);
      if (tmp->next == NULL)
	return ;
      tmp = tmp->next;
    }
}

void		XMLDumpOpeningSegment(int fd, segment *seg)
{
  int		depth = 0;
  int		nb_tab = 0;

  while (g_human_readable == 1 && depth < seg->depth)
    {
      nb_tab = 0;
      while (nb_tab < g_nb_spacer)
	{
	  dprintf(fd, "\t");
	  nb_tab++;
	}
      depth++;
    }
  if (seg->name != NULL)
    dprintf(fd, "<%s>", seg->name);
  if (seg->name == NULL && seg->parent != NULL && seg->parent->type == STAB)
    dprintf(fd, "<%s>", seg->parent->name);
  if (g_human_readable == 1)
    dprintf(fd, "\n");
}

void		XMLDumpClosingSegment(int fd, segment *seg)
{
  int		depth = 0;
  int		nb_tab = 0;

  while (g_human_readable == 1 && depth < seg->depth)
    {
      nb_tab = 0;
      while (nb_tab < g_nb_spacer)
	{
	  dprintf(fd, "\t");
	  nb_tab++;
	}
      depth++;
    }
  if (seg->name != NULL)
    dprintf(fd, "</%s>", seg->name);
  if (seg->name == NULL && seg->parent != NULL && seg->parent->type == STAB)
    dprintf(fd, "</%s>", seg->parent->name);
  if (g_human_readable == 1)
    dprintf(fd, "\n");
}

void		XMLDumpSegment(int fd, segment *seg)
{

  if (seg == NULL)
    return ;
  if (seg->type == STAB)
    {
      XMLDumpAllSegment(fd, seg->child);
      return ;
    }
  XMLDumpOpeningSegment(fd, seg);
  XMLDumpAllElement(fd, seg->element, seg->depth + 1);
  XMLDumpAllSegment(fd, seg->child);
  XMLDumpClosingSegment(fd, seg);
}

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

void		XMLwriting(int fd, message *msg)
{
  while (msg != NULL && msg->segment != NULL && msg->segment->parent != NULL)
    msg->segment = msg->segment->parent;
  while (msg != NULL && msg->segment != NULL && msg->segment->prev != NULL)
    msg->segment = msg->segment->prev;
  XMLDumpAllSegment(fd, msg->segment);
}
