#ifndef		__GENERIC_PARSER_H__
# define	__GENERIC_PARSER_H__

# include	"JSONParser.h"
# include	"XMLParser.h"

/*
** Defining the new line sequence.
*/
# define	CRLF		("\r\n")

/*
** Global variables declarations
*/
int		g_nb_spacer;
int		g_human_readable;
char		g_spacer;

/*
** Main prototypes
*/
void		ParserInit();
void		setHumanReadable(char spacer, int nb_tab);

/*
** Token parser prototypes
*/
char		**token_parse(char *path, char *sep, const char *to_ignore, const char *to_remove);
void		delete_tab(char **ptr);
unsigned int	count_element(char *file, const char *sep);
char		*read_file(char *path, size_t *file_size);
char		**add_element(char **ret, char *elem, const char *to_remove);
int		ignore_it(char *segment, const char *to_ignore);

#endif		/* __GENERIC_PARSER_H__ */
