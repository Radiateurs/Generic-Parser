#include	"generic_parser.h"
#include	<stdio.h>

int		main(int ac, char **av)
{
  message	*msg;

  if (ac < 5)
    return (-1);
  ParserInit();
  setHumanReadable(' ', 2);
  if (av[1][0] != '-' || av[3][0] != '-')
    return (-1);
  if (av[1][1] == 'j' || av[1][1] == 'J')
    msg = JSONparse(av[2]);
  if (av[1][1] == 'x' || av[1][1] == 'X')
    msg = XMLparse(av[2]);
  if (av[3][1] == 'x' || av[3][1] == 'X')
    XMLserialize(av[4], msg);
  if (av[3][1] == 'j' || av[3][1] == 'J')
    JSONserialize(av[4], msg);
  deleteMessages(&msg);
  return (0);
}
