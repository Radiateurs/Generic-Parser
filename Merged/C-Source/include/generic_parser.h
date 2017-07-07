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
int		g_human_readable;	// Specify if the output file should be human readable
int		g_nb_spacer;		// Specify the number of spacer for the indentation
char		g_spacer;		// Specify the char spacer ( SPACE or \t ) (default '\t')
char		g_attribut;		// Specify the char used to define an attribut (default '@')
char		g_text;			// Specify the char used to define a text data (defualt '#')
message		*g_msg;			// Global tree.

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

/*
** RTE Callable
*/
double		nfSetHumanReadable(char *sep, int nb_spacer);
double		nfCleanMemory();

#endif		/* __GENERIC_PARSER_H__ */
