#include "simple_shell.h"

int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;
	pid_t pid;
	int w_status, index;
	char **command_inputs;
	char *argv[100];

	index = 0;
	printf("$ ");
	while ((nread = getline(&line, &size, stdin)) != -1)
	{
		printf("%s", line);
		pid = fork();
		
		if (pid == 0)
		{
			line[strcspn(line, "\n")] = '\0';
			command_inputs = string_to_array(line);

			while (command_inputs[index] != NULL)
			{
				printf("hh %s", command_inputs[index]);
				argv[index] = command_inputs[index];
				index++;
			}
			argv[index] = NULL;

			if (execve(command_inputs[0], argv, NULL) == -1)
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
