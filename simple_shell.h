#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

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
char **string_to_array(char *s);
char *_getenv(const char *name);
void print_path_directories(void);
list_t *build_path_list(void);
int user_exit(char **args, char *line);
