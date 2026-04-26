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
		argv = tokenize(line); 

    /* 3. Check for built-ins BEFORE execution */
    	if (argv != NULL && argv[0] != NULL)
    	{
        	if (strcmp(argv[0], "exit") == 0)
        	{
           	 exit(0);
        	}
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
