#ifndef		__GLOBAL_C__
# define	__GLOBAL_C__

# include	"generic_parser.h"

/*
** Init global variable. See more in generic_parser.h
*/

int		g_human_readable = 0;
int		g_nb_spacer = 0;
char		g_spacer = ' ';
char		g_attribut = '@';
char		g_text = '#';
int		g_fd = 0;
int		g_flux_id = 0;
message		*g_msg = NULL;
char		**g_file_flux = NULL;

#endif		/* __GLOBAL_C__ */
