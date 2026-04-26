#include "simple_shell.h"

/**
 * main - entry point of the program
 * Return: 0
 */
int main(void)
{
    char *line = NULL;
    size_t size = 0;
    ssize_t nread;
    int found = 0;
    char *full_path = NULL;
    char **parsed_args = NULL;
    int last_status = 0;
    int i;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("$ ");

        nread = getline(&line, &size, stdin);
        if (nread == -1)
            break;

        line[strcspn(line, "\n")] = '\0';

        if (line[0] == '\0')
            continue;

        parsed_args = string_to_array(line);
        if (parsed_args == NULL || parsed_args[0] == NULL)
        {
            free(parsed_args);
            continue;
        }

        if (strcmp(parsed_args[0], "exit") == 0)
        {
            int exit_status = last_status;
            if (parsed_args[1] != NULL)
                exit_status = atoi(parsed_args[1]);

            for (i = 0; parsed_args[i] != NULL; i++)
                free(parsed_args[i]);
            free(parsed_args);
            free(line);
            exit(exit_status);
        }

        if (strcmp(parsed_args[0], "env") == 0)
        {
            print_env();
            for (i = 0; parsed_args[i] != NULL; i++)
                free(parsed_args[i]);
            free(parsed_args);
            continue;
        }

        for (i = 0; parsed_args[i] != NULL; i++)
            free(parsed_args[i]);
        free(parsed_args);

        found = 0;
        full_path = get_available_path(line, &found);
        if (found == 0)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", line);
            free(full_path);
            last_status = 127;
            continue;
        }

        last_status = handle_parent_child_action(line, full_path);
        free(full_path);
    }
    free(line);
    return (last_status);
}
