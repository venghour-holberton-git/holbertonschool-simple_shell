#include <stdio.h>

/**
 * main - compares envp and environ addresses
 * Return: 0
 */

extern char **environ;

int main(int argc, char **argv, char **envp)
{
printf("Address of envp:    %p\n", (void *)envp);
printf("Address of environ: %p\n", (void *)environ);

return (0);
}
