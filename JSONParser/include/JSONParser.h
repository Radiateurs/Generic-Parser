#ifndef		__JSONPARSER_H__
# define	__JSONPARSER_H__

# include	<unistd.h>
# include	<stdlib.h>
# include	<string.h>

# include	"string_utils.h"
# include	"message.h"

# ifndef	__TREE_PARSER__
#  define	__TREE_PARSER__

typedef	struct	s_tree_parser	tree_parser;	// Need to be first declarated for the 
						//following prototypes and includes

# endif		/* __TREE_PARSER__ */

# include	"state.h"
# include	"tree_type.h"

/*
** Global Variable declarations
*/
int		g_nb_tab;
int		g_human_readable;

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

message		*JSONparse(char *path);
void		JSONserialize(const char *path, message *msg);
char		**token_parse(char *path);
message		*create_tree(char **tabToken);
void		delete_tab(char **tab);
void	        JSONwriting(int fd, message *msg);
void		JSONinit();
void		setHumanReadable(int nb_tab);

/*
** Dump functions
*/
void		JSONwriting(int fd, message *msg);
void		JSONDumpAllSegment(int fd, segment *seg);
void		JSONDumpSegment(int fd, segment *seg);
void		JSONDumpAllElement(int fd, element *elem, int depth);
void		JSONDumpElement(int fd, element *elem, int depth);



#endif		/*__JSONPARSER_H__ */
