#include "simple_shell.h"

int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;
	pid_t pid;
	int w_status;

	printf("$ ");
	while ((nread = getline(&line, &size, stdin)) != -1)
	{
		printf("%s", line);
		pid = fork();
		
		if (pid == 0)
		{
			line[strcspn(line, "\n")] = '\0';
			char *argv[] = {line, NULL};

			if (execve(line, argv, NULL) == -1)
            		{
                		perror("Error");
               			 exit(1);
            		}
		}
		else
		{
			waitpid(pid, &w_status, WUNTRACED | WCONTINUED);
			printf("$ ");
		}
	}
	return (0);
}
