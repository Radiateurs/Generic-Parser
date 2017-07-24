#ifndef		__PARSING_H__
# define	__PARSING_H__

/*
** JSON Section
*/
double		nfJSONParseFile(char *path);
double		nfJSONParseFlux(int fd);
double		nfJSONFeedFlux();

/*
** XML Section
*/
double		nfXMLParseFile(char *path);

#endif		/* __PARSING_H__ */
