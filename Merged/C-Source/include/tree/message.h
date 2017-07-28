#ifndef		__MESSAGE_H__
# define	__MESSAGE_H__

# include	"segment.h"

enum		e_msg_type
  {
    JSON = 0,
    XML = 1,
    CSV = 2,
    EDIFACT = 3,
    UNKNOWN = 4
  };

typedef struct	s_msg message;

typedef struct	s_msg
{
  message	*next;
  message	*prev;
  unsigned int	id;
  enum e_msg_type	type;
  char		*name;
  segment	*segment;
}		message;

/* Intern functions */
int		deleteMessages(message **old);
int		deleteIDmessage(message **old, unsigned int id);
int		addMessage(message **old, message *new);
int		newMessage(message **old, unsigned int id);
int		switchToIDMessage(message **msg, unsigned int id);
unsigned int	getLastIDMessage(message *msg);
void		dumpMessage(message *old);

/* RTE callable functions */
int		bfDump();
int		bfDeleteMessages();
int		bfDeleteMessage(double id);
int		bfSwitchToIDMessage(double id);
int		bfNewMessage(double id);

#endif		/* __MESSAGE_H__ */
