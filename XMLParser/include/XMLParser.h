#ifndef		__XMLPARSER_H__
# define	__XMLPARSER_H__

# include	<unistd.h>
# include	<stdlib.h>
# include	<string.h>

# include	"message.h"

typedef	struct	s_tree_parser	tree_parser;

enum            e_state
  {
    DECLARATIONB,	// The encountered token is the begining of a variable.
    DECLARATIONE,	// The encountered token is the ending of a variable.
    ASSIGNEMENT,	// The encountered token means that the foolowing token and fraglents should be the content.
    VALUE,		// The encountered token means that it's a value with no token.
    TYPETOKENB,		// The encountered token is a type token begining.
    TYPETOKENE,		// The encountered token is a type token ending.
    SEPARATOR,		// The encountered token is a separator.
    LISTB,		// The encountered token is the begining of a list.
    LISTE,		// The encountered token is the ending of a list.
    TABB,		// The encountered token is the begining of a tab.
    TABE,		// The encountered token is the ending of a tab.
    NONE,		// The encountered token is not knonw.
    ERROR		// Supposed that there is a syntax error.
  };

enum            e_tree_type
  {
    MESSAGE,	// Should add a message in the tree
    SEGMENT,	// Should add a segment in the tree
    CLOSEGROUP, // Should close the current group (list or tab)
    LIST,	// Should add a list in the tree
    TAB,	// Should add a tab in the tree
    ELEMENT,	// Should add an element in the tree
    ATTRIBUT,	// Should add an attribut (content without name or attribut with a name) in the tree
    NAME,	// The encountered token means that this is a variable name for the tree
    CONTENT,	// The encountered token means that this is a variable name for the tree
    NOPE	// Unknown tree type token. Might be a variable, content type or just something else.
  };

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
};

/*
** Prototypes
*/

int		strcis(const char *str, char c);

void		XMLparse(char *path);
char		**token_parse(char *path);
message		*create_tree(char **tabToken);
void		delete_tab(char **tab);

#endif		/*__XMLPARSER_H__ */
