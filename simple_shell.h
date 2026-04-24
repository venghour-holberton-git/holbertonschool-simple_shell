#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Acess to system environment variables */
extern char **environ;


/**
 * struct list_s - singly linked list
 * @dir: directory string
 * @next: pointer to next node
 */

typedef struct list_s
{
    char *dir;
    struct list_s *next;
} list_t;

/* Prototype for task 6 */
void print_env(void);

char **string_to_array(char *s);
char *_getenv(const char *name);
void print_path_directories(void);
list_t *build_path_list(void);
int user_exit(char **args, char *line);
char *search_for_path(char *short_path, int *is_founded);
char *get_available_path(char *user_command, int *is_founded);
int exec_child_command(char ***command_inputs, char **argv);
void set_command(char ***command_inputs, char **argv);

#endif
