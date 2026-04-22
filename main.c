#include "simple_shell.h"

int main(int ac, char **av)
{
	int i = 0;
	int j = 0;
	char **string_array;
	char *path;

	path = _getenv("PATH");

   	if (path != NULL)
        printf("PATH = %s\n", path);

	string_array = string_to_array("hello my main");
	while (string_array[j] != NULL)
	{
		printf("usually %s\n", string_array[j]);
		j++;
	}
	while (av[i] != NULL)
	{
		printf("parameter at index %d is %s\n", i, av[i]);
		i++;
	}
	print_path_directories();

	return (0);
}
