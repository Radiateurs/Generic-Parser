#include	"JSONParser.h"

int		main(int ac, char **av)
{
  message	*msg;

  if (ac < 3)
    return (-1);
  JSONinit();
  msg = JSONparse(av[1]);
  setHumanReadable(1);
  JSONserialize(av[2], msg);
  return (0);
}
