#include "simple_shell.h"

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
