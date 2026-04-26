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
	int found = 0;
	char *full_path = NULL;
	char **args = parse_line(line);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		nread = getline(&line, &size, stdin);
		if (nread == -1)
			break;
		if (_strcmp(args[0], "exit") == 0)
    		user_exit(args, line);
		if (handle_print_env(line) == 0)
			continue;
		found = 0;
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
