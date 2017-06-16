#ifndef		__XMLTREE_TYPE_H__
# define	__XMLTREE_TYPE_H__

# ifndef	__XMLTREE_PARSER__
#  define	__XMLTREE_PARSER__

typedef	struct	s_XMLtree_parser	XMLtree_parser; // Need to be first declarated for the following prototypes

# endif		/* __XMLTREE_PARSER__ */

#include	"tree_type.h"

/* Prototypes */
void		XMLidentify_token_type(const char *fragment, XMLtree_parser *info);
void		XMLadd_segment(XMLtree_parser *info, message **msg);
void		XMLadd_chunk_to_tree(XMLtree_parser *info, message **msg);
int		XMLmodifyListInTab(segment **old, const char *childs_name);
void		XMLfindAndModifyListInTab(segment **old);

#endif		/* __XMLTREE_TYPE_H__ */
