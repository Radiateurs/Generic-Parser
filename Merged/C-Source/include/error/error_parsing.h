#ifndef		__ERROR_PARSING_H__
# define	__ERROR_PARSING_H__

/*
** In this section you'll find everything about the parsing error code.
** They all start with 1XX
*/

/*
** When they start with 10X the error code is about synthax error during parsing
*/
# define	P_N_UNEXPECTED_TOKEN		(100)
# define	P_N_SHOULD_BE_DECLARATION	(101)
# define	P_N_SHOULD_BE_ASSIGNEMENT	(102)
# define	P_N_UNKNOWN_TYPE		(103)
# define	P_N_NOT_CLOSED_SECTION		(105)

# define	P_S_UNEXPECTED_TOKEN		("Unexpected token at %s\n")
# define	P_S_SHOULD_BE_DECLARATION	("The next statement at %s %s should be a declaration\n")
# define	P_S_SHOULD_BE_ASSIGNEMENT	("Assignement token expected at %s\n")
# define	P_S_UNKNOWN_TYPE		("Unknown type at %s %s\n")
# define	P_S_NOT_CLOSED_SECTION		("The section %s isn't closed\n")

#endif		/* __ERROR_PARSING_H__ */
