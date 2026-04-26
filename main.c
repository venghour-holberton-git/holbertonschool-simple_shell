#include "simple_shell.h"

/**
 * main - entry point of the program
 * Return: 0
 */

int main(int argc, char **argv)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;
	int found = 0;
	char *full_path = NULL;
	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		nread = getline(&line, &size, stdin);
		if (nread == -1)
			break;
		if (argv[0] != NULL && strcmp(argv[0], "exit") == 0)
		{
			free(argv);
			free(line);
			exit(EXIT_SUCCESS);
		}
		found = 0;
		if (handle_print_env_and_exit(line) == 0)
			continue;
		full_path = get_available_path(line, &found);
		if (found == 0)
		{
			perror("Error");
			free(full_path);
			continue;
		}
		handle_parent_child_action(line, full_path);
		free(full_path);
	}
	free(line);
	return (0);
}
