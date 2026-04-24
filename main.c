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
	int found = 0;
	int interactive = isatty(STDIN_FILENO);
	char *full_path = NULL;

	printf("$ ");
	while ((nread = getline(&line, &size, stdin)) != -1)
	{
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
		full_path = get_available_path(line, &found);
		printf("founded is %d\n", found);
		if (found == 0)
		{
			free(command_inputs);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			printf("testing");
			exec_child_command(&command_inputs, argv);
			return (0);
		}
		else
		{
			waitpid(pid, &w_status, WUNTRACED | WCONTINUED);
			free(command_inputs);
			printf("$ ");
			fflush(stdout);
		}
	}
	return (0);
}
