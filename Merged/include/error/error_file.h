#ifndef		__ERROR_FILE_H__
# define	__ERROR_FILE_H__

/*
** In this header you'll find avery error relative to files.
** They all start by 2XX.
*/

/*
** 20X : Opening Error
*/
# define	F_N_FILE_DOESNT_EXIST		(200)
# define	F_N_OPEN_FAILS			(201)
# define	F_N_FILE_NAME_NULL		(202)

# define	F_S_FILE_DOESNT_EXIST		("Error [File] : The asked file %s doesn't exist\n")
# define	F_N_OPEN_FAILS			("Error [File] : The open function failed to open %s\n")
# define	F_N_FILE_NAME_NULL		("Error [File] : Can't open a file if the file name isn't provided\n")

/*
** 21X : Reading error
*/
# define	F_N_WRONG_FD			(210)
# define	F_N_NOTHING_TO_READ		(211)
# define	F_N_READ_FAILED			(212)

# define	F_S_WRONG_FD			("Error [File] : The file descriptor given isn't correct\n")
# define	F_S_NOTHING_TO_READ		("Error [File] : The file doesn't have anything to read in it\n")
# define	F_S_READ_FAILED			("Error [File] : The read function failed to read\n")

#endif		/* __ERROR_FILE_H__ */
