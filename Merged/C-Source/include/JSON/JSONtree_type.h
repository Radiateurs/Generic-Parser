#ifndef		__JSONTREE_TYPE_H__
# define	__JSONTREE_TYPE_H__

# ifndef	__JSONTREE_PARSER__
#  define	__JSONTREE_PARSER__

typedef	struct	s_JSONtree_parser	JSONtree_parser; // Need to be first declarated for the following prototypes

# endif		/* __JSONTREE_PARSER__ */

#include	"tree_type.h"

/* Prototypes */
void		JSONidentify_token_type(const char *fragment, JSONtree_parser *info);
void		JSONadd_segment(JSONtree_parser *info, message **msg);
void		JSONadd_chunk_to_tree(JSONtree_parser *info, message **msg);

#endif		/* __JSONTREE_TYPE_H__ */
