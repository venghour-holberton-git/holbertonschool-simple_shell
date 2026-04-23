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
	char full_path[1024];
	int found;
	int interactive = isatty(STDIN_FILENO);

	while ((nread = getline(&line, &size, stdin)) != -1)
	{
		char *path = strdup(_getenv("PATH"));
		char *dir;

		index = 0;
		found = 0;
		
		if (interactive)
		{
			printf("$ ");
			fflush(stdout);
		}
		line[strcspn(line, "\n")] = '\0';
		command_inputs = string_to_array(line);
		dir = strtok(path, ":");
		if (strchr(command_inputs[0], '/') != NULL)
		{
    			if (access(command_inputs[0], X_OK) == 0)
    			{
				strcpy(full_path, command_inputs[0]);
        			argv[0] = command_inputs[0];
        			found = 1;
   		 	}
		}
		else
		{
			while(dir != NULL)
			{
				sprintf(full_path, "%s/%s", dir, command_inputs[0]);
				if (access(full_path, X_OK) == 0)
				{
					found = 1;
					argv[0] = full_path;
					index++;
					break;
				}
				dir = strtok(NULL, ":");
			}
		}	
		if (found == 0)
		{
			free(command_inputs);
			free(path);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			while (command_inputs[index] != NULL)
			{
				argv[index] = command_inputs[index];
				index++;
			}
			argv[index] = NULL;

			if (execve(argv[0], argv, NULL) == -1)
            		{
                		perror("Error");
				free(command_inputs);
				free(path);
               			 exit(1);
            		}
		}
		else
		{
			waitpid(pid, &w_status, WUNTRACED | WCONTINUED);
			free(command_inputs);
			free(path);
		}
	}
	return (0);
}
