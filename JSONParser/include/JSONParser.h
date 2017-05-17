#ifndef		__JSONPARSER_H__
# define	__JSONPARSER_H__

# include	<unistd.h>
# include	<stdlib.h>
# include	<string.h>

# include	"message.h"

typedef	struct	s_tree_parser	tree_parser;

enum            e_state
  {
    DECLARATIONB = 0,	// The encountered token is the begining of a variable.
    DECLARATIONE = 1,	// The encountered token is the ending of a variable.
    ASSIGNEMENT = 2,	// The encountered token means that the foolowing token and fraglents should be the content.
    ESNAME = 3,		// The last token implied that the surrent token is not a token but an alement name.
    VALUE = 4,		// The encountered token means that it's a value with no token.
    TYPETOKENB = 5,	// The encountered token is a type token begining.
    TYPETOKENE = 6,	// The encountered token is a type token ending.
    SEPARATOR = 7,	// The encountered token is a separator.
    LISTB = 8,		// The encountered token is the begining of a list.
    LISTE = 9,		// The encountered token is the ending of a list.
    TABB = 10,		// The encountered token is the begining of a tab.
    TABE = 11,		// The encountered token is the ending of a tab.
    NONE = 12,		// The encountered token is not knonw.
    ERROR = 13		// Supposed that there is a syntax error.
  };

enum            e_tree_type
  {
    MESSAGE = 0,	// Should add a message in the tree
    SEGMENT = 1,	// Should add a segment in the tree
    CLOSEGROUP = 2,	// Should close the current group (list or tab)
    LIST = 3,		// Should add a list in the tree
    TAB = 4,		// Should add a tab in the tree
    ELEMENT = 5,	// Should add an element in the tree
    ATTRIBUT = 6,	// Should add an attribut (content without name or attribut with a name) in the tree
    NAME = 7,		// The encountered token means that this is a variable name for the tree
    CONTENT = 8,	// The encountered token means that this is a variable name for the tree
    NOPE = 9		// Unknown tree type token. Might be a variable, content type or just something else.
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

int		strcis(const char *str, char c);

void		JSONparse(char *path);
char		**token_parse(char *path);
message		*create_tree(char **tabToken);
void		delete_tab(char **tab);

#endif		/*__JSONPARSER_H__ */
