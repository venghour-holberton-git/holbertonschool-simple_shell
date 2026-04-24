#include "simple_shell.h"

/**
 * main - entry point of the program
 * Return: 0
 */

int main(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;
	char *argv[100];
	int found = 0;
	char *full_path = NULL;

	printf("$ ");
	while ((nread = getline(&line, &size, stdin)) != -1)
	{
		found = 0;
		if (handle_print_env_and_exit() == 0)
			continue;
		full_path = get_available_path(line, &found);
		if (found == 0)
		{
			perror("Error");
			printf("$ ");
			fflush(stdout);
			continue;
		}
		handle_parent_child_action(line, full_path);
	}
	return (0);
}
