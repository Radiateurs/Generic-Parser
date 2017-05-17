#ifndef		__ATTRIBUT_H__
# define	__ATTRIBUT_H__

typedef struct	s_att attribut;

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

typedef struct	s_att
{
  attribut	*next;
  attribut	*prev;
  char		*name; // max 32 char
  unsigned int	id;
  type		type;
  char		*content;
}		attribut;

/* Intern functions */
void		dumpAttribut(attribut *att, int depth);
int		deleteIDAttribut(attribut **old, unsigned int id);
int		deleteAttributs(attribut **old);
int		newAttribut(attribut **old, const char *name, unsigned int id, \
			    const char *content, enum e_attr_type type);
unsigned int	lastAttributID(attribut *attr);

/* RTE callable functions */
int		bfNewAttribut(const char *name, double id, const char *content, const char *type);

#endif		/* __ATTRIBUT_H__ */
