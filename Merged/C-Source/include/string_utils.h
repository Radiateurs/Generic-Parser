#ifndef		__STRING_UTILS_H__
# define	__STRING_UTILS_H__

# include	<string.h>
# include	<unistd.h>
# include	<stdlib.h>

int		strcis(const char *str, char c); // Return 0 if c is contained in str. -1 if not.

char		*clean(const char *src, const char *to_ignore);	// Clean out src by erasing every char 
								// contained in to_ignore. 
								// Return  the clean version.

char		*mconcat(char *saved, char *buff);	//Return an allocated string that contains a concatenated
							//versions af saved and buff.

char		**mtab_concat(char **first, char **second);	// Return an allocated tab (char **) that contains
								// a concatained versions of first and second.

int		str_is_num(const char *str);	//Return 0 if the whole str contains only number char ('0' - '9')
						//Retrun -1 if doesn't contains only number.

int		str_n_is_num(const char *str, int max); // Same as str_is_num but will verify max bytes.

int		is_a_token(const char *fragment, const char *sep);	// Return 0 if the whole fragment contains 
									// only token defined in sep.
									// Return -1 if not.

char		*int_to_string(int value);

#endif		/* __STRING_UTILS_H__ */
