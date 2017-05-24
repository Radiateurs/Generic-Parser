#ifndef		__XMLPARSER_H__
# define	__XMLPARSER_H__

# include	<unistd.h>
# include	<stdlib.h>
# include	<string.h>

# include	"string_utils.h"
# include	"message.h"

# ifndef	__TREE_PARSER__
#  define	__TREE_PARSER__

typedef	struct	s_tree_parser	tree_parser; // Need to be first declarated for the following include

# endif		/* __TREE_PARSER__ */

# include	"state.h"
# include	"tree_type.h"

struct		s_tree_parser
{
  enum e_state	last_state;
  enum e_state	current_state;
  enum e_attr_type	value_type;
  enum e_tree_type	last_tree_type;
  enum e_tree_type	current_tree_type;
  int		is_in_list;
  int		is_in_tab;
  char		*seg_name;
  char		*elem_name;
  char		*attr_name;
  char		*content;
  char		*error;
  char		textChar;
  char		attrChar;
};

/*
** Prototypes
*/

int		strcis(const char *str, char c);
char		*mconcat(char *first, char *second);

void		XMLparse(char *path);
char		**token_parse(char *path);
message		*create_tree(char **tabToken);
void		delete_tab(char **tab);

#endif		/*__XMLPARSER_H__ */
