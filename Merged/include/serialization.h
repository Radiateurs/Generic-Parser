#ifndef		__SERIALIZATION_H__
# define	__SERIALIZATION_H__

/*
** XML Section
*/
double		nfXMLSerialize(char *path);
double		nfXMLSerializeMode(char *path, int flags);

/*
** JSON Section
*/
double		nfJSONSerialize(char *path);
double		nfJSONSerializeMode(char *path, int flags);

#endif		/* __SERIALIZATION_H__ */
