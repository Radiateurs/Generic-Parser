#include	"JSONParser.h"

int		main(int ac, char **av)
{
  if (ac < 2)
    return (-1);
  JSONparse(av[1]);
  return (0);
}
