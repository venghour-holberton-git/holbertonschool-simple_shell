#include "simple_shell.h"
#include <stddef.h>

char **string_to_array(char *s)
{
	int word_count = 0;
	char **word_array = NULL;
	char *str, *token;

	if (s == NULL)
		return (NULL);
	for (word_count = 0, str = strdup(s); ; str = NULL, word_count++)
	{
		token = strtok(str, " ");
		if (token == NULL)
			break;
		word_array = realloc(word_array, (word_count + 1) * sizeof(char *));
		word_array[word_count] = token;
	}
	word_array = realloc(word_array, (word_count + 1) * sizeof(char *));
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

