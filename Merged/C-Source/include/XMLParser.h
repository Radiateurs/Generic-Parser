#ifndef		__XMLPARSER_H__
# define	__XMLPARSER_H__

# include	<unistd.h>
# include	<stdlib.h>
# include	<string.h>

# include	"generic_parser.h"
# include	"string_utils.h"
# include	"tree/message.h"

# ifndef	__XMLTREE_PARSER__
#  define	__XMLTREE_PARSER__

typedef	struct	s_XMLtree_parser	XMLtree_parser; // Need to be first declarated for the following include

# endif		/* __XMLTREE_PARSER__ */

# include	"XML/XMLstate.h"
# include	"XML/XMLtree_type.h"

/*
** Defining string that won't change.
*/
# define	XMLSEPARATOR		("\'<>/\"= ")
# define	XMLTO_IGNORE		(" \t\r\n")
# define	XMLTO_REMOVE		("\t\r\n")

struct		s_XMLtree_parser
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
  char		*content;
  char		*error;
};

/*
** Prototypes
*/
message		*XMLparse(char *path);
message		*XMLcreate_tree(char **tabToken);
void		XMLfeed_tree(message *msg, char **tokens, int id, int reset);
message		*XMLparseFlux(int *fd, int id); // In JSONparse.c
void		XMLfeedFlux(int *fd, message *msg, int id); // In JSONparse.c
void		XMLserialize(const char *path, message *msg);
void		XMLserializeMode(const char *path, message *msg, int flags);
char		**XMLtoken_parse(char *path, const char *separator, const char *to_ignore, const char *to_remove);
char		**XMLtoken_parse_flux(int *fd, const char *separator, const char *to_ignore, const char *to_remove);
int		segmentHasNoText(segment *seg);

/*
** Dump functions prototypes
*/
void		XMLwriting(int fd, message *msg);
void		XMLDumpAllSegment(int fd, segment *seg);
void		XMLDumpSegment(int fd, segment *seg);
void		XMLDumpAllElement(int fd, element *elem, int depth);
void		XMLDumpElement(int fd, element *elem, int depth);

/*
** RTE Callable
*/
double		nfXMLParseFile(char *path);
double		nfXMLSerialize(char *path);
double		nfXMLSerializeMode(char *path, int flags);

#endif		/*__XMLPARSER_H__ */
