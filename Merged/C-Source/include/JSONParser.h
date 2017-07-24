#ifndef		__JSONPARSER_H__
# define	__JSONPARSER_H__

# include	<unistd.h>
# include	<stdlib.h>
# include	<string.h>

# include	"generic_parser.h"
# include	"string_utils.h"
# include	"tree/message.h"

# ifndef	__JSONTREE_PARSER__
#  define	__JSONTREE_PARSER__

typedef	struct	s_JSONtree_parser	JSONtree_parser;// Need to be first declarated for the 
							//following prototypes and includes

# endif		/* __JSONTREE_PARSER__ */

# include	"JSON/JSONstate.h"
# include	"JSON/JSONtree_type.h"

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
message		*JSONparse(char *path); // In JSONparse.c
message		*JSONparseFlux(int *fd, int id); // In JSONparse.c
void		JSONfeedFlux(int *fd, message *msg, int id); // In JSONparse.c
message		*JSONcreate_tree(char **tabToken); // In JSON/create_tree.c
void		JSONfeed_tree(message *msg, char **tokens, int id, int reset);
void		JSONserialize(const char *path, message *msg); // In JSONparse.c
void		JSONserializeMode(const char *path, message *msg, int flags); // In JSONparse.c
void	        JSONwriting(int fd, message *msg); // In JSON/serialize.c

/*
** Dump functions (all in JSON/serialize.c)
*/
void		JSONwriting(int fd, message *msg);
void		JSONDumpAllSegment(int fd, segment *seg);
void		JSONDumpSegment(int fd, segment *seg);
void		JSONDumpAllElement(int fd, element *elem, int depth);
void		JSONDumpElement(int fd, element *elem, int depth);

/*
** RTE callable (all in JSON/rte_callable.c)
*/
double		nfJSONParseFile(char *path);
double		nfJSONParseFlux(int fd);
double		nfJSONFeedFlux();
double		nfJSONSerialize(char *path);
double		nfJSONSerializeMode(char *path, int flags);

#endif		/*__JSONPARSER_H__ */
