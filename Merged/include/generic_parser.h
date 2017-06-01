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

#endif		/* __GENERIC_PARSER_H__ */
