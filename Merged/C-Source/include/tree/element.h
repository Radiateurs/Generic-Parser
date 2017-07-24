#ifndef		__ELEMENT_H__
# define	__ELEMENT_H__

typedef enum    e_attr_type
  {
    ALPHA = 0,
    NUM = 1,
    ALNUM = 2,
    STRING = 3,
    INTEGER = 4,
    DECIMAL = 5,
    BOOL = 6,
    DATE = 7,
    TIME = 8,
    NULLOBJ = 9,
    UNKNOW = 10
  }             type;

typedef struct	s_elem element;

typedef struct	s_elem
{
  element	*next;
  element	*prev;
  unsigned int	id;
  char		*name; //max 32 char
  enum e_attr_type	type; // Defined at the begining.
  char		*content; // content is the value. Was the attribut structure before (gain of memory).
}		element;

/* Intern functions */
int		addElement(element **old, element *new); // CONSTRUCTOR
int		newElement(element **old, const char *name, unsigned int id, \
			   const char *content, enum e_attr_type type); // CONSTRUCTOR
element		*cloneElement(element *origin); //CONSTRUCTOR

int		deleteIDElement(element **old, unsigned int id); // DESTRUCTOR
int		deleteElements(element **old); // DESTRUCTOR

element		*getIDElement(element *elem, unsigned int id); // GETTER
int		countElement(element *elem); // GETTER
unsigned int	lastElementID(element *elem); // GETTER
void		dumpElement(element *elem, int depth); // PRINTER

/* RTE callable functions */
double		nfLastElementID();
int		bfNewElement(const char *name, double id);
int		bfNewElementChild(const char *name, double id);

#endif		/* __ELEMENT_H__ */
