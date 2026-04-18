#include "simple_shell.h"

int main(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;
	
	printf("$ ");
	while((nread = getline(&line, &size, stdin)) != -1)
	{
		printf("%s", line);
		printf("$ ");
	}
	return (0);
}
