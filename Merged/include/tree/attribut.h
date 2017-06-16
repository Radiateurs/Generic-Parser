#ifndef		__ATTRIBUT_H__
# define	__ATTRIBUT_H__

typedef struct	s_att attribut;


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
