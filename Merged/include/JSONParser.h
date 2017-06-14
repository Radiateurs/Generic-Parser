#ifndef		__JSONPARSER_H__
# define	__JSONPARSER_H__

# include	<unistd.h>
# include	<stdlib.h>
# include	<string.h>

# include	"generic_parser.h"
# include	"string_utils.h"
# include	"message.h"

# ifndef	__JSONTREE_PARSER__
#  define	__JSONTREE_PARSER__

typedef	struct	s_JSONtree_parser	JSONtree_parser;// Need to be first declarated for the 
							//following prototypes and includes

# endif		/* __JSONTREE_PARSER__ */

# include	"JSONstate.h"
# include	"JSONtree_type.h"

/*
** Defining string that won't change.
*/
# define	JSONSEPARATOR		("\",{}[]:")
# define	JSONTO_IGNORE		(" \t\r\n")
# define	JSONTO_REMOVE		("\t\r\n")

struct		s_JSONtree_parser
{
  enum e_state	last_state;
  enum e_state	current_state;
  enum e_attr_type	value_type;
  enum e_tree_type	last_tree_type;
  enum e_tree_type	current_tree_type;
  int		is_in_list;
  int		is_in_tab;
  int		list_in_tab;
  char		*seg_name;
  char		*elem_name;
  char		*attr_name;
  char		*content;
  char		*error;
};

/*
** Prototypes
*/

message		*JSONparse(char *path);
message		*JSONcreate_tree(char **tabToken);
void		JSONserialize(const char *path, message *msg);
void		JSONserializeMode(const char *path, message *msg, int flags);
void	        JSONwriting(int fd, message *msg);

/*
** Dump functions
*/
void		JSONwriting(int fd, message *msg);
void		JSONDumpAllSegment(int fd, segment *seg);
void		JSONDumpSegment(int fd, segment *seg);
void		JSONDumpAllElement(int fd, element *elem, int depth);
void		JSONDumpElement(int fd, element *elem, int depth);

#endif		/*__JSONPARSER_H__ */
