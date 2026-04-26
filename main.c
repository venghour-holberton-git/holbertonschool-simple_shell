#include "simple_shell.h"

/**
 * main - entry point of the program
 * Return: 0
 */

#include "simple_shell.h"

/**
 * main - entry point of the program
 * Return: 0
 */
int main(int argc, char **args)
{
    char *line = NULL;
    size_t size = 0;
    ssize_t nread;
    int found = 0;
    char *full_path = NULL;
    char **parsed_args = NULL;
    (void)argc;
    (void)args;

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
            user_exit(parsed_args, line);
        }
        if (strcmp(parsed_args[0], "env") == 0)
        {
            print_env();
            free(parsed_args);
            continue;
        }

        free(parsed_args);

        found = 0;
        full_path = get_available_path(line, &found);
        if (found == 0)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", line);
            free(full_path);
            continue;
        }
        handle_parent_child_action(line, full_path);
        free(full_path);
    }
    free(line);
    return (0);
}
