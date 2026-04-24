#include "simple_shell.h"

/**
 * main - entry point of the program
 * Return: 0
 */

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t pid;
    int status;
    char *argv[2];
    int i;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("$ ");

        read = getline(&line, &len, stdin);

        if (read == -1)
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        i = strlen(line) - 1;
        while (i >= 0 && (line[i] == ' ' || line[i] == '\t'))
        {
            line[i] = '\0';
            i--;
        }

        if (line[0] == '\0')
            continue;

        pid = fork();
        if (pid == -1)
            continue;

        if (pid == 0)
        {
            argv[0] = line;
            argv[1] = NULL;

            execve(line, argv, environ);

            exit(127);
        }
        else
        {
            wait(&status);
        }
    }

    free(line);
    return 0;
}
