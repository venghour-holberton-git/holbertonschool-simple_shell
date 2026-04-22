#include "simple_shell.h"

int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;
	pid_t pid;
	int w_status, index = 0;
	char **command_inputs;
	char *argv[100];
	char full_path[1024];

	printf("$ ");
	while ((nread = getline(&line, &size, stdin)) != -1)
	{
		printf("%s", line);
		pid = fork();
		index = 0;
		
		if (pid == 0)
		{
			char *path = strdup(getenv("PATH"));
			char *dir;

			line[strcspn(line, "\n")] = '\0';
			command_inputs = string_to_array(line);
			dir = strtok(path, ":");

			while(dir != NULL)
			{
				sprintf(full_path, "%s/%s", dir, command_inputs[0]);
				if (access(full_path, X_OK) == 0)
				{
					argv[0] = full_path;
					index++;
					break;
				}
				dir = strtok(NULL, ":");
			}

			while (command_inputs[index] != NULL)
			{
				argv[index] = command_inputs[index];
				index++;
			}
			argv[index] = NULL;

			if (execve(argv[0], argv, NULL) == -1)
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
