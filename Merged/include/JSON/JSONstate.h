#ifndef		__JSONSTATE_H__
# define	__JSONSTATE_H__

# ifndef	__JSONTREE_PARSER__
#  define	__JSONTREE_PARSER__

typedef	struct	s_JSONtree_parser	JSONtree_parser; // Need to be first declarated for the following prototypes

# endif		/* __JSONTREE_PARSER__ */

# include	"state.h"

/* Prototypes*/
void		JSONstate_non_token_fragment(char **tokens, JSONtree_parser *info, int *i, message *msg);
void		JSONstate_token_fragment(const char *fragment, JSONtree_parser *info, message *msg);

#endif		/* __JSONSTATE_H__ */
