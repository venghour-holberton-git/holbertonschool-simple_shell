#include "simple_shell.h"

int main(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;
	pid_t pid;
	int w_status, index = 0;
	char **command_inputs;
	char *argv[100];
	char *full_path;
	int found;
	int interactive = isatty(STDIN_FILENO);

	printf("$ ");
	while ((nread = getline(&line, &size, stdin)) != -1)
	{
		char *path = strdup(_getenv("PATH"));
		char *dir;

		index = 0;
		found = 0;
		
		if (interactive)
		{
			if (strcmp(line, "env\n") == 0)
			{
				print_env();
				printf("$ ");
				continue;
			}
		}
		line[strcspn(line, "\n")] = '\0';
		command_inputs = string_to_array(line);
		dir = strtok(path, ":");

		if (strcmp(command_inputs[0], "exit") == 0)
		{
    	/* Clean up: free allocated memory for arguments and input buffer /
    	free_args(args); 
    	free(input_line);

    	/ Terminate the program with status 0 (success) */
    	exit(EXIT_SUCCESS);
		}

		full_path = get_available_path(line, &found);
		if (found == 0)
		{
			free(command_inputs);
			free(path);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			exec_child_command(&command_inputs, argv);
			return (0);
		}
		else
		{
			waitpid(pid, &w_status, WUNTRACED | WCONTINUED);
			free(command_inputs);
			free(path);
			printf("$ ");
                        fflush(stdout);
		}
	}
	return (0);
}
