#include "simple_shell.h"
#include <stddef.h>

/**
 * user_exit - checks if command is "exit" and handles termination
 * @args: array of parsed command arguments
 * @line: raw input line from getline
 * @last_status: tracks last command exit status
 * Description: Frees allocated memory and exits shell if command is "exit"
 *
 * Return: 0 if command is not "exit"
 */

int user_exit(char **args, char *line, int last_status)
{
    int exit_status = last_status;
    int i;

    if (args[0] != NULL && strcmp(args[0], "exit") == 0)
    {
        if (args[1] != NULL)
            exit_status = atoi(args[1]); 

        for (i = 0; args[i] != NULL; i++)
            free(args[i]);
        free(args);
        free(line);
        exit(exit_status);
    }
    return (0);
}

/**
 * print_env - prints the current environment variables
 *
 * Description: This function iterates through the global environment
 * variable list and prints each entry on a new line.
 *
 * Return: void
 */
void print_env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}

/**
 * search_for_path - searches for an executable in PATH directories
 * @short_path: command name without path
 * @is_founded: pointer to flag indicating if command is found
 *
 * Description: This function searches for the given command name
 * in all directories listed in the PATH environment variable.
 * It constructs a full path for each directory and checks if the
 * file is executable using access(). If found, the full path is returned.
 *
 * Return: pointer to the full path of the executable. If not found,
 * returns the last constructed path (flag remains 0)
 */

char *search_for_path(char *short_path, int *is_founded)
{
	char *full_path;
	char *dir;
	char *path = strdup(_getenv("PATH"));

	*is_founded = 0;
	full_path = malloc(1024);
	dir = strtok(path, ":");
	if (dir == NULL)
	{
		free(short_path);
		free(path);
		return (full_path);
	}
	while (dir != NULL)
	{
		sprintf(full_path, "%s/%s", dir, short_path);
		if (access(full_path, X_OK) == 0)
		{
			free(short_path);
			free(path);
			*is_founded = 1;
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}
	free(short_path);
	free(path);
	return (full_path);
}

/**
 * get_available_path - resolves the executable path for a command
 * @user_command: raw input command from the user
 * @is_founded: pointer to flag indicating if command is found
 *
 * Description: This function extracts the command from the user input.
 * If the command contains a '/' character, it is treated as a direct
 * path and checked for executability. Otherwise, it searches for the
 * command in the PATH environment variable using search_for_path().
 *
 * Return: pointer to the resolved executable path. If not found,
 * returns a path with is_founded set to 0
 */

char *get_available_path(char *user_command, int *is_founded)
{
	char **command_array;
	char *first_input;
	int i;

	*is_founded = 0;
	user_command[strcspn(user_command, "\n")] = '\0';
	command_array = string_to_array(user_command);
	first_input = strdup(command_array[0]);
	for (i = 0; ;i++)
	{
		if (command_array[i] == NULL)
			break;
		free(command_array[i]);
	}
	free(command_array);
	if (strchr(first_input, '/') != NULL)
	{
		if (access(first_input, X_OK) == 0)
		{
			*is_founded = 1;
			return (first_input);
		}
	}
	return (search_for_path(first_input, is_founded));
}

/**
 * get_argv_from_command - builds argument vector for execve
 * @user_command: raw command line input from the user
 * @file_path: full path to the executable command
 *
 * Description: This function splits the user command into tokens and
 * constructs an argv array suitable for execve. The first element
 * of argv is replaced with the provided full path to the executable.
 *
 * Return: pointer to the newly created argv array, or NULL on failure
 */

char **get_argv_from_command(char *user_command, char *file_path)
{
	int index = 0;
	char **argv;
	char **command_inputs;

	argv = malloc(sizeof(char *) * 100);
	command_inputs = string_to_array(user_command);
	while (command_inputs[index] != NULL)
	{
		if (index == 0)
		{
			argv[index] = file_path;
		}
		else
		{
			argv[index] = command_inputs[index];
		}
		index++;
	}
	argv[index] = NULL;
	return (argv);
}
