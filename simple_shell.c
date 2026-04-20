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
