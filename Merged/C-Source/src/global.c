#ifndef		__GLOBAL_C__
# define	__GLOBAL_C__

# include	"generic_parser.h"

/*
** Init global variable. See more in generic_parser.h
*/

int		g_human_readable = 0; // Used as a boolean. Tells if the user has set the serialize mode in human readable or not.
int		g_nb_spacer = 0; // Tells the number of spacer to use.
char		g_spacer = ' '; // Tells the spaces. By defualt its SPACE
char		g_attribut = '@'; // To tell if the element is an attribut. @ by default.
char		g_text = '#'; // To tell if the element is a texte
int		g_fd = 0; // Global file descriptor for XXXParseFlux
int		g_flux_id = 0; // ID of the flux message
message		*g_msg = NULL; // Global graph. MOST IMPORTANT VARIABLE
char		**g_file_flux = NULL; // Container of the flux (to concatenate the informations that could have been cut.

#endif		/* __GLOBAL_C__ */
