#ifndef		__ELEMENT_H__
# define	__ELEMENT_H__

# include	"attribut.h"

typedef struct	s_elem element;

typedef struct	s_elem
{
  element	*next;
  element	*prev;
  unsigned int	id;
  char		*name; //max 32 char
  attribut	*attribut;
}		element;

/* Intern functions */
int		addElement(element **old, element *new);
void		dumpElement(element *elem, int depth);
int		deleteIDElement(element **old, unsigned int id);
int		deleteElements(element **old);
int		newElement(element **old, const char *name, unsigned int id);
unsigned int	lastElementID(element *elem);

/* RTE callable functions */
double		nfLastElementID();
int		bfNewElement(const char *name, double id);
int		bfNewElementChild(const char *name, double id);

#endif		/* __ELEMENT_H__ */
