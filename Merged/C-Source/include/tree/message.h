#ifndef		__MESSAGE_H__
# define	__MESSAGE_H__

# include	"segment.h"

// For beta 1.2 or 1.3
enum		e_msg_type
  {
    JSON = 0,
    XML = 1,
    CSV = 2,
    EDI = 3,
    UNKNOWN = 4
  };

typedef struct	s_msg message;

typedef struct	s_msg
{
  message	*next;
  message	*prev;
  unsigned int	id;
  segment	*segment;
}		message;

/* Intern functions */
int		deleteMessages(message **old);
int		deleteIDmessage(message **old, unsigned int id);
int		newMessage(message **old, unsigned int id);
int		switchToIDMessage(message **msg, unsigned int id);
int		getLastIDMessage(message *msg);
void		dumpMessage(message *old);

/* RTE callable functions */
int		bfDump();
int		bfDeleteMessages();
int		bfDeleteMessage(double id);
int		bfSwitchToIDMessage(double id);
int		bfNewMessage(double id);

#endif		/* __MESSAGE_H__ */
