#include	"XMLParser.h"

int		main(int ac, char **av)
{
  message	*msg;

  XMLinit();
  if (ac < 3)
    return (-1);
  msg = XMLparse(av[1]);
  setHumanReadable(1);
  XMLserialize(av[2], msg);
  return (0);
}
