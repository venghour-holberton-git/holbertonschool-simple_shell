#include "simple_shell.h"
#include "new_shell.h"

/**
 * main - entry point of the program
 * Return: 0
 */

int main(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;
	char *full_path;
	pid_t cpid;
	char *argv[100];
	int wstatus;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		nread = getline(&line, &size, stdin);
		if (nread == -1)
			exit(1);
		line[strcspn(line, "\n")] = '\0';
		full_path = line;
		if (access(full_path, X_OK) == 0)
		{
			cpid = fork();
			if (cpid == 0)
			{
				argv[0] = full_path;
				argv[1] = NULL;
				if (execve(full_path, argv, environ) == -1)
				{
					perror("Error");
					exit(1);
				}
			}
			else
			{
				waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
			}
		}
		perror("Error");
	}
	return 0;
}
