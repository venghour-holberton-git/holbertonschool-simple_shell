#include "simple_shell.h"
#include <stddef.h>

char **string_to_array(char *s)
{
	int word_count = 0;
	char **word_array;
	char *str, *token;

	if (s == NULL)
		return (NULL);
	word_array = malloc(sizeof(char *) * 1024);
	for (word_count = 0, str = strdup(s); ; str = NULL, word_count++)
	{
		token = strtok(str, " ");
		if (token == NULL)
			break;
		word_array[word_count] = token;
	}
	word_array[word_count] = NULL;
	return (word_array);
}

/**
 * _getenv - gets an environment variable
 * @name: name of the variable to search for
 *
 * Return: pointer to value if found, NULL otherwise
 */

extern char **environ;

char *_getenv(const char *name)
{
    int i, j;
    int match;

    if (name == NULL || *name == '\0')
        return (NULL);

    for (i = 0; environ[i] != NULL; i++)
    {
        match = 1;

        for (j = 0; name[j] != '\0'; j++)
        {
            if (environ[i][j] != name[j])
            {
                match = 0;
                break;
            }
        }

        if (match && environ[i][j] == '=')
            return (&environ[i][j + 1]);
    }

    return (NULL);
}
void print_path_directories(void)
{
    int i;
    char *path;
    char *token;

    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path = environ[i] + 5;

            token = strtok(path, ":");

            while (token != NULL)
            {
                printf("%s\n", token);
                token = strtok(NULL, ":");
            }
            return;
        }
    }
}
list_t *build_path_list(void)
{
    int i;
    char *path;
    char *token;
    list_t *head = NULL;
    list_t *new_node;
    list_t *tmp;

    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path = strdup(environ[i] + 5);
            if (path == NULL)
                return (NULL);

            token = strtok(path, ":");

            while (token != NULL)
            {
                new_node = malloc(sizeof(list_t));
                if (new_node == NULL)
                {
                    free(path);
                    return (NULL);
                }

                new_node->dir = strdup(token);
                new_node->next = NULL;

                if (head == NULL)
                {
                    head = new_node;
                }
                else
                {
                    tmp = head;
                    while (tmp->next != NULL)
                        tmp = tmp->next;
                    tmp->next = new_node;
                }

                token = strtok(NULL, ":");
            }

            free(path);
            return (head);
        }
    }

    return (NULL);
}

/**
 * user_exit - Checks if a command is "exit" and handles termination.
 * @args: Array of tokens (the command and its arguments).
 * @line: The raw input buffer from getline to be freed.
 * Return: 0 if the command is not exit, otherwise it exits the shell.
 */

/**
 * int user_exit(char **args, char *line)
{
	if (args && args[0] != NULL)
	{
		if (_strcmp(args[0], "exit") == 0)
		{
			free_tokens(args);
			free(line);

			exit(EXIT_SUCCESS);
		}
	}

	return (0);
}


*/
/**
 * print_env - prints the environment variables
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
char *search_for_path(char *short_path, int *is_founded)
{
	char *full_path = NULL;
	int index = 0;
	char *dir;
	char *path = strdup(_getenv("PATH"));

	full_path = malloc(1024);
	dir = strtok(path, ":");
	while(dir != NULL)
	{
		sprintf(full_path, "%s/%s", dir, short_path);
		if (access(full_path, X_OK) == 0)
		{
			*is_founded = 1;
			return (full_path);
		}
		index++;
	}
	return (full_path);
}
char *get_available_path(char *user_command, int *is_founded)
{
	char *first_input;
	char **command_array;

	*is_founded = 0;
	user_command[strcspn(user_command, "\n")] = '\0';
	command_array = string_to_array(user_command);
	first_input = strdup(command_array[0]);
	free(command_array);
	if (strchr(first_input, '/') != NULL)
        {
		if (access(first_input, X_OK) == 0)
                {
                        *is_founded = 1;
			return (first_input);
                }
	}
        else
        {
		return (search_for_path(first_input, is_founded));
        }
}
/**
int exec_command(char **command_input, char *path)
{
	char *directory;
}
*/
