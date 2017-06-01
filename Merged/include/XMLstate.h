#ifndef		__XMLSTATE_H__
# define	__XMLSTATE_H__

# ifndef	__XMLTREE_PARSER__
#  define	__XMLTREE_PARSER__

typedef	struct	s_XMLtree_parser	XMLtree_parser; // Need to be first declarated for the following prototypes

# endif		/* __XMLTREE_PARSER__ */

# include	"state.h"

/* Prototypes*/
void		XMLstate_non_token_fragment(char **tokens, XMLtree_parser *info, int *i);
void		XMLstate_token_fragment(const char *fragment, XMLtree_parser *info);
void		XMLgetTextData(int *i, char **tokens, XMLtree_parser *info);

#endif		/* __XMLSTATE_H__ */
