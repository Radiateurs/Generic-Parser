#ifndef		__ACCESS_MESSAGE_C__
# define	__ACCESS_MESSAGE_C__

# include	"generic_parser.h"
# include	"navigation/movement.h"

double		nfGetMessageID()
{
  if (g_msg == NULL)
    return (-1);
  return ((double)g_msg->id);
}

double		nfGetMessageType()
{
  if (g_msg == NULL)
    return (-1);
  return (g_msg->type);
}

char		*tfGetMessageName()
{
  if (g_msg == NULL)
    return ("");
  if (g_msg->name == NULL)
    return ("");
  return (g_msg->name);
}

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
