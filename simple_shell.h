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
char *search_for_path(char *short_path, int *is_founded);
char *get_available_path(char *user_command, int *is_founded);
int exec_child_command(char *user_command, char *file_path);
char **get_argv_from_command(char *user_command, char *file_path);
int handle_parent_child_action(char *line, char *full_path);
int handle_print_env_and_exit(char *line);

#endif
