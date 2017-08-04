#ifndef		__ACCESS_MESSAGE_C__
# define	__ACCESS_MESSAGE_C__

# include	"generic_parser.h"
# include	"navigation/movement.h"

// Returns message's ID
double		nfGetMessageID()
{
  if (g_msg == NULL)
    return (-1);
  return ((double)g_msg->id);
}

// Returns message's type
double		nfGetMessageType()
{
  if (g_msg == NULL)
    return (-1);
  return (g_msg->type);
}

// Returns message's name
char		*tfGetMessageName()
{
  if (g_msg == NULL)
    return ("");
  if (g_msg->name == NULL)
    return ("");
  return (g_msg->name);
}

// Returns the specifyed id message's type 
double		nfGetIDMessageType(int id)
{
  int		error;
  int		last_id;
  int		real_type;

  if (g_msg == NULL)
    return (-1);
  last_id = g_msg->id;
  if ((error = nfGoToIDMessage(id)) != 0)
    return (error);
  real_type = g_msg->type;
  nfGoToIDMessage(last_id);
  return (real_type);
}

// Returns the specifyed id message's name 
char		*tfGetIDMessageName(int id)
{
  int		error;
  int		last_id;
  char		*real_name;

  if (g_msg == NULL)
    return ("");
  last_id = g_msg->id;
  if ((error = nfGoToIDMessage(id)) != 0)
    return ("");
  real_name = g_msg->name;
  nfGoToIDMessage(last_id);
  if (real_name == NULL)
    return ("");
  return (real_name);
}

// Returns the specifyed type message's id 
double		nfGetTypeMessageID(int type)
{
  int		error;
  int		last_id;
  int		real_id;

  if (g_msg == NULL)
    return (-1);
  last_id = g_msg->id;
  if ((error = nfGoToTypeMessage(type)) != 0)
    return (error);
  real_id = g_msg->id;
  nfGoToIDMessage(last_id);
  return (real_id);
}

// Returns the specifyed id message's name 
char		*tfGetTypeMessageName(int type)
{
  int		error;
  int		last_id;
  char		*real_name;

  if (g_msg == NULL)
    return ("");
  last_id = g_msg->id;
  if ((error = nfGoToTypeMessage(type)) != 0)
    return ("");
  real_name = g_msg->name;
  nfGoToIDMessage(last_id);
  if (real_name == NULL)
    return ("");
  return (real_name);
}

// Returns the specifyed name message's id 
double		nfGetNameMessageID(char *name)
{
  int		error;
  int		last_id;
  int		real_id;

  if (g_msg == NULL)
    return (-1);
  last_id = g_msg->id;
  if ((error = nfGoToNameMessage(name)) != 0)
    return (error);
  real_id = g_msg->id;
  nfGoToIDMessage(last_id);
  return (real_id);
}

// Returns the specifyed name message's type 
double		nfGetNameMessageType(char *name)
{
  int		error;
  int		last_id;
  int		real_type;

  if (g_msg == NULL)
    return (-1);
  last_id = g_msg->id;
  if ((error = nfGoToNameMessage(name)) != 0)
    return (error);
  real_type = g_msg->type;
  nfGoToIDMessage(last_id);
  return (real_type);
}

#endif		/* __ACCESS_MESSAGE_C__ */
