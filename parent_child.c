#include "simple_shell.h"

/**
 * exec_child_command - executes a command in the child process
 * @user_command: raw command line input from the user
 * @file_path: full path to the executable command
 *
 * Description: This function prepares the argument vector using
 * get_argv_from_command and executes the command using execve.
 * If execve fails, an error message is printed.
 *
 * Return: 1 on failure, does not return on success
 */

int exec_child_command(char *user_command, char *file_path)
{
	char **argv, **command_inputs;
	int i = 0;
	
	command_inputs = string_to_array(user_command);
	argv = get_argv_from_command(user_command, file_path);
	if (execve(argv[0], argv, NULL) == -1)
	{
		while (command_inputs[i] != NULL)
		{
			free(command_inputs[i]);
			i++;
		}
		free(command_inputs);
		free(argv);
		perror("Error");
		return (1);
	}
	return (1);
}

/**
 * handle_parent_child_action - handles process creation and execution
 * @line: raw command line input from the user
 * @full_path: full path to the executable command
 *
 * Description: This function forks a new process. The child process
 * executes the command, while the parent waits for the child process
 * to finish and then prints a new prompt.
 *
 * Return: void
 */

void handle_parent_child_action(char *line, char *full_path)
{
	int w_status;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		exec_child_command(line, full_path);
		return;
	}
	else
	{
		waitpid(pid, &w_status, WUNTRACED | WCONTINUED);
	}
}

/**
 * handle_print_env_and_exit - handles "env" command in interactive mode
 * @line: user input
 * Description: This function checks if the shell is running in
 * interactive mode. If so, it compares the user input with the
 * "env" command. When matched, it prints the environment variables
 * and displays a new prompt.
 *
 * Return: 0 if the "env" command is handled successfully,
 * -1 otherwise
 */

int handle_print_env(char *line)
{
	int interactive = isatty(STDIN_FILENO);

	if (interactive)
	{
		if (strcmp(line, "env\n") == 0)
		{
			print_env();
			return (0);
		}
	}
	return (-1);
}
