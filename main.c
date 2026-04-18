#include "simple_shell.h"

int main(int ac, char ** av)
{
	int i = 0;

	while (av[i] != NULL)
	{
		printf("parameter at index %d is %s\n", i, av[i]);
		i++;
	}
	return (0);
}
