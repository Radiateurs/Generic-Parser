#ifndef		__SEGMENT_H__
# define	__SEGMENT_H__

# include	"element.h"

typedef struct	s_seg segment;

# define	SSEG	(0)
# define	SLIST	(1)
# define	STAB	(2)

typedef struct	s_seg
{
  segment	*next;
  segment	*prev;
  segment	*parent;
  segment	*child;
  int		type;
  unsigned int	id;
  char		*name; //max 32 char
  int		is_a_group;
  int		depth;
  element	*element;
}		segment;

/* Intern functions */
// CONSTRUCTOR
segment		*initSegment(const char *name, unsigned int id, int is_a_group,	\
			     int depth, int seg_type);
segment		*copySegment(segment *to_copy);
segment		*cloneSegment(segment *origin);
int		addChild(segment **old_parent, segment *child);
int		addSegment(segment **old, segment *to_add, int is_a_child);
int		newSegment(segment **old, const char *name, unsigned int id, int is_a_group, int is_a_child, \
			   int depth, int type);
// DESTRUCTOR
void		removeIDChild(segment **old_parent, unsigned int id);
void		removeIDSegment(segment **old, unsigned int id);
int		deleteIDSegment(segment **old, unsigned int id);
int		deleteChildSegment(segment **old);
int		deleteSegments(segment **old);
int		deleteListSegments(segment **old);
void		closeGroupSegment(segment **old);
// GETTER
int		getSegmentType(segment *seg);
segment		*getIDSegment(segment *seg, unsigned int id);
unsigned int	lastGroupID(segment *seg);
unsigned int	lastSegmentID(segment *seg);
unsigned int	getNextID(segment *seg);
int		countSegment(segment *seg);
void		increaseChildDepth(segment **old);
// Serializer
void		dumpSegment(segment *seg);
void		dumpSegmentChild(segment *seg);

/* RTE callable functions */
double		nfLastGroupID();
double		nfLastSegmentID();
int		bfDeleteIDSegment(double id);
int		bfNewGroup(const char *name, double id);
int		bfNewSegment(const char *name, double id);

#endif		/* __SEGMENT_H__ */
