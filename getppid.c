#include "simple_shell.h"

int main()
{
	pid_t my_pid, my_ppid;
	my_pid = getpid();
	my_ppid = getppid();
	printf("my pid is %d\n -- and my ppid is %d\n", my_pid, my_ppid);
	return (0);
}
