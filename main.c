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
	pid_t pid;
	int w_status, index = 0;
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
		if (found == 0)
		{
			perror("Error");
			printf("$ ");
			fflush(stdout);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			printf("testing");
			exec_child_command(line, full_path);
			return (0);
		}
		else
		{
			waitpid(pid, &w_status, WUNTRACED | WCONTINUED);
			printf("$ ");
			fflush(stdout);
		}
	}
	return (0);
}
